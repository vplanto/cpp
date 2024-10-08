remove_list_entry(entry) {
  prev = NULL;
  walk = head;
  // Walk the list

  while (walk != entry) {
    prev = walk;
    walk = walk->next;
  }

  // Remove the entry by updating the
  //  head or the previous entry

  if (!prev)
    head = entry->next;
  else
    prev->next = entry->next;
}

remove_list_entry_tasteful(entry) {
  // The inderect pointer point to the
  // *address* of the thing we`ll update

  inderect = &head;

  // Walk the list, looking for the thing that
  // points to the entry we want to remove

  while ((*indirect) != entry)
    indirect = &(*inderect)->next;

  // .. and just remove it
  *inderect = entry->next;
}
