cwd = getcwd() // /home/kali/crack_me/save_scooby
cwd_len = strlen(cwd) // 31
i = 0
/*
	if cwd[i] == '/' set to '$'
	if cwd[i] is alphabetical and upper case += 0x1E
	if cwd[i] is alphabetical and lower case -= 0x1E
*/
while (i < cwd_len)
{
	if (cwd[i] == 0x2F)  // '/'
		cwd[i] = 0x24 // '$' 
	else 
		if (cwd[i] <= 0x60 || cwd[i] > 0x7A) // <='`' || >'z' 
			if (cwd[i] > 0x40 && cwd[i] <= 0x5A)  //  >'@' & <= 'Z'
				cwd[i] += 0x1E
						
			
		else
			cwd[i] -= 0x1E
		i++
}



