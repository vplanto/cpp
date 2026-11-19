/*
 * Кейс Clarke (1946): перевірка розподілу влучань V-1 у Лондоні за критерієм Пірсона (chi^2).
 * Об'єднує теми 1-го семестру: struct, new[]/delete[], const&, <fstream>, <sstream>, <iomanip>.
 * (08-io/poisson_chi2.cpp)
 */

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

struct PoissonBin {
  std::string label;
  int k;
  bool isTail;
  int observed;
  double expected;
  double chi2Term;
};

bool isCommentOrEmpty(const std::string& line) {
  for (std::size_t i = 0; i < line.size(); ++i) {
    char ch = line[i];
    if (ch == ' ' || ch == '\t' || ch == '\r') {
      continue;
    }
    return ch == '#';
  }
  return true;
}

bool tryParseTotalHits(const std::string& line, int& totalHits) {
  const std::string prefix = "# total_hits:";
  if (line.rfind(prefix, 0) != 0) {
    return false;
  }
  std::stringstream ss(line.substr(prefix.size()));
  int value = 0;
  if (ss >> value && value > 0) {
    totalHits = value;
    return true;
  }
  return false;
}

int countDataRows(const std::string& path, int& totalHitsFromMeta) {
  std::ifstream file(path);
  if (!file.is_open()) {
    return -1;
  }

  int count = 0;
  std::string line;
  while (std::getline(file, line)) {
    tryParseTotalHits(line, totalHitsFromMeta);
    if (!isCommentOrEmpty(line)) {
      ++count;
    }
  }
  return count;
}

bool loadBins(const std::string& path, PoissonBin* bins, int count) {
  std::ifstream file(path);
  if (!file.is_open()) {
    return false;
  }

  int index = 0;
  std::string line;
  while (std::getline(file, line) && index < count) {
    if (isCommentOrEmpty(line)) {
      continue;
    }

    std::stringstream ss(line);
    std::string label;
    std::string kStr;
    std::string tailStr;
    std::string obsStr;

    if (!std::getline(ss, label, ',') || !std::getline(ss, kStr, ',') ||
        !std::getline(ss, tailStr, ',') || !std::getline(ss, obsStr, ',')) {
      return false;
    }

    bins[index].label = label;
    bins[index].k = std::stoi(kStr);
    bins[index].isTail = (std::stoi(tailStr) != 0);
    bins[index].observed = std::stoi(obsStr);
    bins[index].expected = 0.0;
    bins[index].chi2Term = 0.0;
    ++index;
  }

  return index == count;
}

void computePoissonExpectations(PoissonBin* bins, int count, double lambda,
                                int totalSquares) {
  // Рекурентне обчислення P(k) = P(k-1) * lambda / k уникає переповнення k!.
  double prob = std::exp(-lambda);
  double cumulativeProb = 0.0;

  for (int i = 0; i < count; ++i) {
    if (i > 0) {
      prob *= lambda / static_cast<double>(bins[i].k);
    }

    double binProb = bins[i].isTail ? (1.0 - cumulativeProb) : prob;
    if (!bins[i].isTail) {
      cumulativeProb += prob;
    }

    bins[i].expected = static_cast<double>(totalSquares) * binProb;
    double diff = static_cast<double>(bins[i].observed) - bins[i].expected;
    bins[i].chi2Term = (diff * diff) / bins[i].expected;
  }
}

void printTable(const PoissonBin* bins, int count) {
  std::cout << std::left << std::setw(8) << "k" << std::right << std::setw(12)
            << "Observed" << std::setw(12) << "Expected" << std::setw(14)
            << "(O-E)^2/E" << '\n';
  std::cout << std::string(46, '-') << '\n';

  std::cout << std::fixed << std::setprecision(2);
  for (int i = 0; i < count; ++i) {
    std::cout << std::left << std::setw(8) << bins[i].label << std::right
              << std::setw(12) << bins[i].observed << std::setw(12)
              << bins[i].expected << std::setw(14) << bins[i].chi2Term << '\n';
  }
}

// Згортає хвостові біни з E_i < minExpected у спільний останній бін (>= k).
double computeMergedChi2(const PoissonBin* bins, int count, double minExpected,
                         int& mergedCount, int& mergedTailObs,
                         double& mergedTailExp) {
  double chi2 = 0.0;
  mergedCount = 0;
  mergedTailObs = 0;
  mergedTailExp = 0.0;

  int splitIndex = count;
  double tailSum = 0.0;
  for (int i = count - 1; i >= 0; --i) {
    tailSum += bins[i].expected;
    splitIndex = i;
    if (tailSum >= minExpected) {
      break;
    }
  }

  for (int i = 0; i < splitIndex; ++i) {
    chi2 += bins[i].chi2Term;
    ++mergedCount;
  }

  for (int i = splitIndex; i < count; ++i) {
    mergedTailObs += bins[i].observed;
    mergedTailExp += bins[i].expected;
  }
  double diff = static_cast<double>(mergedTailObs) - mergedTailExp;
  chi2 += (diff * diff) / mergedTailExp;
  ++mergedCount;

  return chi2;
}

int main(int argc, char* argv[]) {
  std::string dataPath = (argc > 1) ? argv[1] : "08-io/clarke_1946.csv";
  int totalHits = 0;
  int binCount = countDataRows(dataPath, totalHits);
  if (binCount < 0 && argc <= 1) {
    dataPath = "clarke_1946.csv";
    binCount = countDataRows(dataPath, totalHits);
  }

  if (binCount <= 0) {
    std::cerr << "Помилка: не вдалося прочитати дані з " << dataPath << '\n';
    return 1;
  }

  PoissonBin* bins = new PoissonBin[binCount];
  if (!loadBins(dataPath, bins, binCount)) {
    std::cerr << "Помилка: некоректний формат рядків у " << dataPath << '\n';
    delete[] bins;
    bins = nullptr;
    return 1;
  }

  int totalSquares = 0;
  int lowerBoundHits = 0;
  for (int i = 0; i < binCount; ++i) {
    totalSquares += bins[i].observed;
    lowerBoundHits += bins[i].k * bins[i].observed;
  }
  if (totalHits == 0) {
    totalHits = lowerBoundHits;
  }

  double lambda =
      static_cast<double>(totalHits) / static_cast<double>(totalSquares);
  computePoissonExpectations(bins, binCount, lambda, totalSquares);

  std::cout << "Дані Clarke (1946): квадратів = " << totalSquares
            << ", влучень = " << totalHits << ", lambda = " << std::fixed
            << std::setprecision(4) << lambda << "\n\n";

  printTable(bins, binCount);

  double rawChi2 = 0.0;
  for (int i = 0; i < binCount; ++i) {
    rawChi2 += bins[i].chi2Term;
  }

  int mergedBins = 0;
  int mergedTailObs = 0;
  double mergedTailExp = 0.0;
  double mergedChi2 = computeMergedChi2(bins, binCount, 5.0, mergedBins,
                                        mergedTailObs, mergedTailExp);
  int df = mergedBins - 2; // m категорій - 1 (нормування) - 1 (оцінка lambda)
  const double chi2CritAlpha05Df3 = 7.815;

  std::cout << std::fixed << std::setprecision(4);
  std::cout << "\nchi^2 (усі " << binCount << " категорій) = " << rawChi2
            << '\n';
  std::cout << "chi^2 (об'єднаний хвіст E >= 5: останній бін O="
            << mergedTailObs << ", E=" << std::setprecision(2) << mergedTailExp
            << ") = " << std::setprecision(4) << mergedChi2
            << ", df = " << df << '\n';
  std::cout << "Критичне значення (alpha = 0.05, df = 3) = "
            << std::setprecision(3) << chi2CritAlpha05Df3 << '\n';

  if (mergedChi2 < chi2CritAlpha05Df3) {
    std::cout << "Висновок: підстав відхилити гіпотезу випадкового розподілу "
                 "Пуассона немає.\n";
  } else {
    std::cout << "Висновок: дані відхиляються від моделі Пуассона.\n";
  }

  delete[] bins;
  bins = nullptr;
  return 0;
}
