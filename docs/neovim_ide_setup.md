# Налаштування Neovim (C++ Dev Environment) на Ubuntu

Ця інструкція описує процес встановлення та налаштування Neovim з використанням конфігурації NvChad, адаптованої для розробки на C++ (clangd + autoformat).

**Системні вимоги:** Ubuntu 20.04+
**Версія Neovim:** 0.10.0 або новіша

## 1\. Підготовка системи

Встановіть необхідні системні залежності (компілятори, git, unzip, python, ripgrep для пошуку):

```bash
sudo apt update
sudo apt install -y curl git gcc g++ make unzip ripgrep python3-venv
```

## 2\. Встановлення Neovim (AppImage)

Стандартний пакет в Ubuntu (`apt install neovim`) часто застарілий. Використовуємо AppImage для отримання актуальної версії.

```bash
cd ~
curl -LO https://github.com/neovim/neovim/releases/latest/download/nvim.appimage
chmod u+x nvim.appimage
sudo mv nvim.appimage /usr/local/bin/nvim
```

## 3\. Встановлення шрифтів (Nerd Fonts)

Для коректного відображення іконок в NvChad потрібен патчений шрифт. Встановлюємо **JetBrainsMono Nerd Font**.

```bash
mkdir -p ~/.local/share/fonts
cd ~/.local/share/fonts 
curl -fLo "JetBrainsMono.zip" https://github.com/ryanoasis/nerd-fonts/releases/latest/download/JetBrainsMono.zip
unzip -o JetBrainsMono.zip
rm JetBrainsMono.zip
fc-cache -f -v
```

> **Важливо:** Після цього перейдіть у налаштування вашого терміналу (Preferences -\> Profile -\> Text) і оберіть шрифт **JetBrainsMono Nerd Font**.

## 4\. Встановлення NvChad

Клонуємо базову конфігурацію NvChad:

```bash
git clone https://github.com/NvChad/NvChad ~/.config/nvim --depth 1
```

## 5\. Налаштування користувацької конфігурації

Створимо необхідну структуру папок та файли з вашими налаштуваннями.

### 5.1. Створення структури папок

```bash
mkdir -p ~/.config/nvim/lua/custom/configs
```

### 5.2. Головний файл `init.lua` (з виправленням помилок сумісності)

Перезаписуємо стандартний `init.lua` для додавання polyfill (виправлення warning про `get_active_clients`):

```bash
cat > ~/.config/nvim/init.lua << 'EOF'
-- Polyfill for deprecated function in newer Neovim versions
if vim.lsp.get_clients then vim.lsp.get_active_clients = vim.lsp.get_clients end

require "core"

local custom_init_path = vim.api.nvim_get_runtime_file("lua/custom/init.lua", false)[1]

if custom_init_path then
  dofile(custom_init_path)
end

require("core.utils").load_mappings()

local lazypath = vim.fn.stdpath "data" .. "/lazy/lazy.nvim"

-- bootstrap lazy.nvim!
if not vim.loop.fs_stat(lazypath) then
  require("core.bootstrap").gen_chadrc_template()
  require("core.bootstrap").lazy(lazypath)
end

dofile(vim.g.base46_cache .. "defaults")
vim.opt.rtp:prepend(lazypath)
require "plugins"
EOF
```

### 5.3. Список плагінів (`lua/custom/plugins.lua`)

Використовуємо `none-ls` замість застарілого `null-ls`.

```bash
cat > ~/.config/nvim/lua/custom/plugins.lua << 'EOF'
local plugins = {
  {
    "nvimtools/none-ls.nvim",
    event = "VeryLazy",
    opts = function()
      return require "custom.configs.null-ls"
    end,
  },
  {
    "neovim/nvim-lspconfig",
    config = function()
      require "plugins.configs.lspconfig"
      require "custom.configs.lspconfig"
    end,
  },
  {
    "williamboman/mason.nvim",
    opts = {
      ensure_installed = {
        "clangd",
        "clang-format",
        "codelldb",
      }
    }
  }
}

return plugins
EOF
```

### 5.4. Налаштування форматування (`lua/custom/configs/null-ls.lua`)

Вмикає автоформатування при збереженні файлу (`BufWritePre`).

```bash
cat > ~/.config/nvim/lua/custom/configs/null-ls.lua << 'EOF'
local augroup = vim.api.nvim_create_augroup("LspFormatting", {})
local null_ls = require("null-ls")

local opts = {
  sources = {
    null_ls.builtins.formatting.clang_format,
  },
  on_attach = function(client, bufnr)
    if client.supports_method("textDocument/formatting") then
      vim.api.nvim_clear_autocmds({
        group = augroup,
        buffer = bufnr,
      })
      vim.api.nvim_create_autocmd("BufWritePre", {
        group = augroup,
        buffer = bufnr,
        callback = function()
          vim.lsp.buf.format({ bufnr = bufnr })
        end,
      })
    end
  end,
}

return opts
EOF
```

### 5.5. Налаштування LSP Clangd (`lua/custom/configs/lspconfig.lua`)

Вимикає вбудовану підказку сигнатур, щоб уникнути конфліктів інтерфейсу.

```bash
cat > ~/.config/nvim/lua/custom/configs/lspconfig.lua << 'EOF'
local base = require("plugins.configs.lspconfig")
local on_attach = base.on_attach
local capabilities = base.capabilities

local lspconfig = require("lspconfig")

lspconfig.clangd.setup {
  on_attach = function(client, bufnr)
    client.server_capabilities.signatureHelpProvider = false
    on_attach(client, bufnr)
  end,
  capabilities = capabilities,
}
EOF
```

## 6\. Перший запуск

1.  Запустіть Neovim:
    ```bash
    nvim
    ```
2.  Зачекайте, поки менеджер пакетів **Lazy** завантажить всі плагіни.
3.  Зачекайте, поки **Mason** встановить `clangd` та `clang-format` (ви побачите повідомлення в кутку екрану).
4.  Якщо потрібно, виконайте `:MasonInstallAll` всередині редактора, щоб переконатися, що всі інструменти встановлені.
5.  Перезапустіть Neovim.

Тепер ваше середовище готове до роботи з C++.