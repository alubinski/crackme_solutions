check_format(serial)
{
int i, var1, var2
i = var1 = var 2 = 0
while (i < strlen(serial)) 
	{
	if ((___ctype_b_loc()[serial[i]] & 8) != 0) // check if symbol is numeric
		{
		 v1++
		}
	else 
		{
		if ((___ctype_b_loc()[serial[i]] & 0x800) != 0) // check if not alphanumeric
			return 0
		v2++   	     // increase if alphanumeric but not numeric
	i++
	} 
return (strlen(serial) == v1 || strlen(serial) == v2 - 1)
// so keygen must be either all numbers or all letter and 1 number to be correct
}
}

// According to other solutions:
// signs 0-9 are substracted by 0x30 so in checksum they have value 0-9
// signs A-Z are substracted by 0x37 so they are translated to value 10-n
// signs a-z arre firstly upscaled to A-Z than transclated similary
// than values are added and checked if sum is dividable by 7
// but values used in and operations seem weird, if we want to check if char is numeric we should do AND with 0x8 instead of 0x800
// later we do AND with 0x400 but shouldn't it be 0x800 to check if is not alhhanumeric?
// i am confused about bit structure returned by ___ctype_b_loc

is_valid_checksum(serial)
{
int i, var1, var2
i = var1 = var 2 = 0
while (i < strlen(serial))
	{
	if ((___ctype_b_loc()[serial[i]] & 0x800) != 0)  
		var1 += serial[i] - 0x30
	else 
	{
		if((___ctype_b_loc()[serial[i]] & 0x400) == 0) 
			return 0
		var1 += toupper(serial[i]) - 0x37 
	}
	i++
	}
return var1 % 7 == 0
}

blacklist[2] = {"ABC123", "DEF456"}

checkblacklist(serial) 
{
 int i
 for ( i = 0, i < 1, i++) 
 {
 if (!strcmp(serial, &(black_list[i]))) {
 	return 0
 }
 }
 return 1;
}


check(serial)
{
serial_len = strlen(serial)
if (serial_len > 0x14) {
	print("Serial num to long.")
	return
}
if (!check_format(serial)) {
	print("Invalid serial format.")
	return
}	
if (!is_valid_checksum(serial)) {
	print("Invalid checksum.")
	return
}
if (!checkblacklist(serial)) {
	print("Serial numer blacklisted.")
	return
}

print("Serial numer is valid")
}
