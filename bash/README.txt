CS356 Project 1.C README:
Author: Alexander Day, 830 523 317

Files: 
1) asymmetrickey_encr 
	-Encrypts all characters in input file except for the EOF character using RSA algorithm
	-INPUT:
		<file1> : filename of file containing two integers that form a public key
		<file2> : filename of file to encrypt
	Note: files reflecting arguments must be in current working directory
	-TO EXECUTE: ./asymmetric_encr <file1> <file2> 
	-OUTPUT: text file, "Alexander-Day.ciphertext", that contains the encrypted input file

2) asymmetrickey_decr 
	-Decrypts all characters in input file using RSA algorithm
	-INPUT:
		<file3> : filename of file containing two integers that form a private key
		<file4> : filename of file to decrypt
	Note: files reflecting arguments must be in current working directory
	-TO EXECUTE: ./asymmetric_decr <file3> <file4> 
	-OUTPUT: text file, "Alexander-Day.plaintext", that contains the decrypted input file

3) Alexander-Day.key
	-contains public and private key to utilize the above scripts
	-formatted as 2 lines, 1st line: e n, 2nd line: d n
	 where <e,n> forms the public key and <d,n> forms the private key



