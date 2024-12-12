import sys

PW_BUFFER_SIZE = 64     
PW_LEN_MIN = 38         # without /n/0
PW_LEN_MAX = 47         # without /n/0

def swap32(x):
    return (((x << 24) & 0xFF000000) |
            ((x <<  8) & 0x00FF0000) |
            ((x >>  8) & 0x0000FF00) |
            ((x >> 24) & 0x000000FF))

def word_shift(x):
    # step 12 from inner function
    for i in range(32):
        x = (x >> 12) | ((x & 0xff) ^ 0x15)
    return x

def toInt(arr):
    res = 0  
    for i in range(4):
        res |= (ord(arr[i]) << 8*i)
    return res

def check_bytes_00_to_03(beg, pw_len):
    len_buf = [chr(pw_len)] * 4

    pwd_word = toInt(beg)
    len_word = toInt(len_buf)

    pwd_word ^= len_word
    pwd_word = swap32(pwd_word)
    pwd_word = word_shift(pwd_word)

    return pwd_word == 0xef

def check_bytes_16_to_19(mid, end, pw_len):
    len_buf = [chr(pw_len)] * 4

    mid_word = toInt(mid)
    end_word = toInt(end)
    len_word = toInt(len_buf) + 1

    end_word = swap32(end_word)
    mid_word ^= end_word
    mid_word = swap32(mid_word)
    mid_word = word_shift(mid_word)

    mid_word ^= len_word
    mid_word = swap32(mid_word)
    mid_word = word_shift(mid_word)

    return mid_word == 0x6f

def create_password(beg, mid, end):
    print(beg + "all those wh" + mid + "nder are los" + end)


def password_lookup(pw_buffer):
    beg_buf = [' '] * 4
    mid_buf = [' '] * 4
    end_buf = ['\0'] * (PW_LEN_MAX - 32 + 2) # +2 for /n/0
    i = 0

    for pw_len in range(PW_LEN_MIN, PW_LEN_MAX + 1):
        beg = [None] * 4
        
        while True:
            if (check_bytes_00_to_03(beg=beg_buf, pw_len=pw_len)):
                beg = beg_buf
                break
            i = 3
            while (i >= 0):
            #for i in range(3, -1, -1):
                if (beg_buf[i] == ' '):
                    beg_buf[i] = 'A'
                    break
                if (beg_buf[i] < 'Z'):
                    beg_buf[i] = chr(ord(beg_buf[i]) + 1)
                    break
                if (beg_buf[i] == 'Z'):
                    beg_buf[i] = 'a'
                    break
                if (beg_buf[i] <  'z'):
                    beg_buf[i] = chr(ord(beg_buf[i]) + 1)
                    break 
                beg_buf[i] = ' '
                i -= 1
            # if (i < 0):
            #     break
    print(beg)
    end_len = pw_len - 32
    i = end_len
    end_buf[end_len] = '\n'
    end_buf[end_len + 1] = '\0'

    while True:
        if (check_bytes_16_to_19(mid_buf, end_buf, pw_len)):
            create_password(beg, mid_buf, end_buf)
            return
        
        i = 3
        while (i >= 0):
        # for i in range(3, -2, -1):
            if (mid_buf[i] == ' '):
                mid_buf[i] = 'A'
                break
            if (mid_buf[i] < 'Z'):
                mid_buf[i] = chr(ord(mid_buf[i]) + 1)
                break
            if (mid_buf[i] == 'Z'):
                mid_buf[i] = 'a'
                break
            if (mid_buf[i] <  'z'):
                mid_buf[i] = chr(ord(mid_buf[i]) + 1)
                break 
            mid_buf[i] = ' '
            i -= 1

        if (i < 0 ):
            iter_end = 4
            iter_start = 8 if (end_len >= 8) else end_len

            for i in range (iter_start, iter_end, -1) :
                if (end_buf[i] == ' '):
                    end_buf[i] = 'A'
                    break
                if (end_buf[i] < 'Z'):
                    end_buf[i] = chr(ord(end_buf[i]) + 1)
                    break
                if (end_buf[i] == 'Z'):
                    end_buf[i] = 'a'
                    break
                if (end_buf[i] <  'z'):
                    end_buf[i] = chr(ord(end_buf[i]) + 1)
                    break 
                end_buf[i] = ' ' 

            if i < 0:
                break





if __name__ == '__main__':
    pw_buffer = [0] * (PW_LEN_MAX + 1)
    password_lookup(pw_buffer=pw_buffer)

