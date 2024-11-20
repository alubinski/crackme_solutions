import os

def encrypt(cwd):
	keygen=""
	for letter in cwd:
		if letter == '/':
			keygen += '$'
		else:
			if letter.isalpha() and letter.isupper():
				keygen += chr(ord(letter) + 0x1E)
			if letter.isalpha() and letter.islower():
				keygen += chr(ord(letter) - 0x1E)
			else:
				keygen += letter
	print(keygen)
if __name__ == '__main__':
	cwd = os.getcwd()
	encrypt(cwd)
