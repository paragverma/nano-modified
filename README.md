# nano-modified

Title: Adding/Modifying Features of 'GNU Nano' Text Editor

Name: Parag Verma

MIS: 111403068

Description:
	Features which were tweaked/modified-> Shift + Right/Left cursor now selects text.
						Backspace/Tab/Other characters now cut marked text, if any.
						
	Features Added-> Ability to write text to Multiple positions by placing markers. Press Shift + Up to place a marker. Shift + down removes all markers.
			Some basic word completion. Words are contained in a text file named dictionary.txt.
			
	Approach and data structures->
	
		A small change done is to enable Mouse Support by default instead of using '-m' optional argument in terminal.
		
		Functions which handle backspace and tab were modified to cut marked text, if any.
		Also if there is any marked text, then before printing any any character, marked text is cut first.
		
		For storing and acessing positions of markers, a linked list is used, because every position has to analysed even if 1 character has to printed.
		When even 1 marker is active, cursor is moved to that particular position, and output is done there, and then cursor is moved to the original position.
		
		For word prediction, strings are scanned from a text file and stored in a Binary Search tree, so that finding a particular word is fast.
		Also each word predicted is also added to a linked list. Before predicting, the linked list is checked for that word, so that no 2 words
		are repeated.
			
