# AOL_DS — Boogle Slang Dictionary

Boogle is a company that creates and documents new slang words based on the internet. As a programmer at Boogle, you are tasked with building an application that lets users manage and explore Boogle's released slang words.

> ⚠️ **Do not use regex** anywhere in your implementation — it will affect your score.
> Focus on the **main logic and core features**. Design is not scored.

---

## Features

The application has **5 menus**:

1. Release a new slang word
2. Search a slang word
3. View all slang words starting with a certain prefix
4. View all slang words
5. Exit

---

## Menu Details

### 1. Release a New Slang Word

- Prompts the user to enter a new slang word.
  - **Validation:** must be more than 1 character and contain no spaces.
- Prompts the user to enter a description (meaning) of the word.
  - **Validation:** must be more than 2 words.
- Stores the slang word and its description in a **Trie** data structure.
- If the slang word already exists in the Trie, its description is **updated**.

**Example — adding a new word:**
```
Input a new slang word [Must be more than 1 characters and contains no space]: d
Input a new slang word [Must be more than 1 characters and contains no space]: d a
Input a new slang word [Must be more than 1 characters and contains no space]: da
Input a new slang word description [Must be more than 2 words]: The
Input a new slang word description [Must be more than 2 words]: The word the

Successfully released new slang word.
Press enter to continue...
```

**Example — updating an existing word:**
```
Input a new slang word [Must be more than 1 characters and contains no space]: da
Input a new slang word description [Must be more than 2 words]: Same meaning as word "the"

Successfully updated a slang word.
Press enter to continue...
```

---

### 2. Search a Slang Word

- Prompts the user to enter a slang word to search.
  - **Validation:** must be more than 1 character and contain no spaces.
- Searches the word in the Trie.
- If the word is **not found**, displays an appropriate message and returns to the main menu.
- If the word is **found**, displays the word and its description.

**Example — word not found:**
```
Input a slang word to be searched [Must be more than 1 characters and contains no space]: de

There is no word "de" in the dictionary.
Press enter to continue...
```

**Example — word found:**
```
Input a slang word to be searched [Must be more than 1 characters and contains no space]: d
Input a slang word to be searched [Must be more than 1 characters and contains no space]: d a
Input a slang word to be searched [Must be more than 1 characters and contains no space]: da

Slang word  : da
Description : Same meaning as word "the"

Press enter to continue...
```

---

### 3. View All Slang Words Starting with a Prefix

- Prompts the user to enter a prefix to search.
- Searches the Trie for all words that start with the given prefix.
- If no words match, displays an appropriate message.
- If matches are found, lists all matching words in **lexicographical order**.

**Example — prefix not found:**
```
Input a prefix to be searched: de

There is no prefix "de" in the dictionary.
Press enter to continue...
```

**Example — prefix found:**
```
Input a prefix to be searched: da

Words starts with "da":
1. da
2. dadan
3. daijobu
4. dawg
5. dazz

Press enter to continue...
```

---

### 4. View All Slang Words

- If the dictionary is **empty**, displays an appropriate message.
- Otherwise, lists all words in the dictionary in **lexicographical order**.

**Example — empty dictionary:**
```
There is no slang word yet in the dictionary.
Press enter to continue...
```

**Example — dictionary with words:**
```
List of all slang words in the dictionary:
1. da
2. dadan
3. daijobu
4. dawg
5. dazz
6. rizz
7. simp

Press enter to continue...
```

---

### 5. Exit

Closes the application and displays a farewell message.

```
Thank you... Have a nice day :)
```

---

## Data Structure

<<<<<<< HEAD
All slang words must be stored in a **Trie** data structure. This enables efficient prefix-based search and lexicographical ordering of results.
=======
All slang words must be stored in a **Trie** data structure. This enables efficient prefix-based search and lexicographical ordering of results.
>>>>>>> 6dc738c (finishing touches and ascii art)
