# AOL_DS

Boogle is a company that create, and document new slang words based on the internet. You as a programmer working at the Boogle company are asked to create an application that is useful for seeing what slang words have been released by Boogle. Ensure that you didn’t use regex in your work, or it will affect your score. Please focus on the main logic and main feature! (Design are not scored). The requirements are:\n

•	The application consists of 5 menus:\n
1.	Release a new slang word 
2.	Search a slang word 
3.	View all slang words starting with a certain prefix word 
4.	View all slang words
5.	Exit\n

•	If user choose menu 1 (“Release a new slang word”), then the program will:\n
o	Ask the user to input the new slang word. Validate that the slang word must be more than 1 character and contains no space.
o	Ask the user to input the description (meaning) of the new word. Validate that the description must be more than 1 word.
o	Store the new released slang word to a Trie data structure along with its description.







Input a new slang word [Must be more than 1 characters and contains no space]: d
Input a new slang word [Must be more than 1 characters and contains no space]: d a
Input a new slang word [Must be more than 1 characters and contains no space]: da
Input a new slang word description [Must be more than 2 words]: The
Input a new slang word description [Must be more than 2 words]: The word the

Successfully released new slang word.
Press enter to continue...


o	If the slang word already exists in the Trie, then update the description with the new description.

Input a new slang word [Must be more than 1 characters and contains no space]: da
Input a new slang word description [Must be more than 2 words]: Same meaning as word “the”

Successfully updated a slang word.
Press enter to continue...


•	If user choose menu 2 (“Search a slang word”), then the program will:\n
o	Ask the user to input the slang word that want to be searched. Validate that the slang word must be more than 1 character and contains no space.
o	Search the input word in the Trie data structure.
o	If there is no such word, please show empty message for the user and go back to main menu.

Input a slang word to be searched [Must be more than 1 characters and contains no space]: de

There is no word “de” in the dictionary.
Press enter to continue...


o	If there is such word, please show the word along with its description.\n

Input a slang word to be searched [Must be more than 1 characters and contains no space]: d
Input a slang word to be searched [Must be more than 1 characters and contains no space]: d a
Input a slang word to be searched [Must be more than 1 characters and contains no space]: da

Slang word  : da
Description : Same meaning as word “the”

Press enter to continue...


•	If user choose menu 3 (“View all slang words starting with a certain prefix word”), then the program will:
o	Ask the user to input the prefix word that want to be searched. 
o	Search the input word in the Trie data structure.
o	If there is no such word, please show empty message for the user.

Input a prefix to be searched: de

There is no prefix “de” in the dictionary.
Press enter to continue...


o	If there is such word, please show the list of words in the dictionary that starts with the prefix word in lexicographical order.







Input a prefix to be searched: da

Words starts with “da”:
1. da
2. dadan 
3. daijobu
4. dawg
5. dazz

Press enter to continue...


•	If user choose menu 4 (“View all slang words”), then the program will:
o	If there is no word yet in the dictionary, please show empty message for the user.

There is no slang word yet in the dictionary.
Press enter to continue...


o	Else, please show the list of all words in the dictionary in lexicographical order.

List of all slang words in the dictionary:
1. da
2. dadan 
3. daijobu
4. dawg
5. dazz
6. rizz
7. simp

Press enter to continue...


•	If user choose menu 5 (“Exit”), then the program will be closed.

Thank you... Have a nice day :)





