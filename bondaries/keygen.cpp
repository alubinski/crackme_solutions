#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
  PW_BUFSIZE = 64,
  PW_LEN_MIN = 38, // without /n/0
  PW_LEN_MAX = 46, // without /n/0
};

uint32_t swap32(uint32_t x)
{
  return (((x << 24) & 0xFF000000) | ((x << 8) & 0x00FF0000) |
          ((x >> 8) & 0x0000FF00) | ((x >> 24) & 0x000000FF));
}

uint32_t word_calculate_shift(uint32_t word)
{
  for (int i = 0; i < 32; ++i)
    word = (word >> 12) | ((word & 0xff) ^ 0x15);

  return word;
}

int check_bytes_00_to_03(const char *beg, size_t pw_len)
{
  char len_buf[4] = {static_cast<char>(pw_len), static_cast<char>(pw_len),
                     static_cast<char>(pw_len), static_cast<char>(pw_len)};

  uint32_t pwd_word = *(uint32_t *)beg;
  uint32_t len_word = *(uint32_t *)len_buf;

  pwd_word ^= len_word;                      // Pass 1 Step  4
  pwd_word = swap32(pwd_word);               // Pass 1 Step  8
  pwd_word = word_calculate_shift(pwd_word); // Pass 1 Step 12

  return pwd_word == 0xef;
}

int check_bytes_16_to_19(const char *mid, const char *end, size_t pw_len)
{
  char len_buf[4] = {static_cast<char>(pw_len), static_cast<char>(pw_len),
                     static_cast<char>(pw_len), static_cast<char>(pw_len)};

  uint32_t mid_word = *(uint32_t *)mid;
  uint32_t len_word = *(uint32_t *)len_buf;
  uint32_t end_word = *((uint32_t *)end + 1);

  end_word = swap32(end_word);               // Pass 1 Step  2
  mid_word ^= end_word;                      // Pass 1 Step  5
  mid_word = swap32(mid_word);               // Pass 1 Step 9
  mid_word = word_calculate_shift(mid_word); // Pass 1 Step 12

  mid_word ^= len_word;                      // Pass 2 Step  4
  mid_word = swap32(mid_word);               // Pass 2 Step  8
  mid_word = word_calculate_shift(mid_word); // Pass 2 Step 12

  return mid_word == 0x6f;
}

const char *create_password(const char *beg, const char *mid, const char *end,
                            char *pw_buf)
{
  snprintf(pw_buf, PW_BUFSIZE, "%.4sall those wh%.4snder are los%s", beg,
           mid, end);
  return pw_buf;
}

void password_lookup(char *pw_buf)
{
  int pw_len, end_len = 0;
  char beg_buf[5] = {' ', ' ', ' ', ' ', 0};
  char mid_buf[5] = {' ', ' ', ' ', ' ', 0};
  char end_buf[PW_LEN_MAX - 32 + 2];    // +2 for \n\0

  for (pw_len = PW_LEN_MIN; pw_len <= PW_LEN_MAX; ++pw_len)
  {
    while (true)
    {
      if (check_bytes_00_to_03(beg_buf, pw_len))
        break;
      for (int i = 4; i--;)
      {
        if (beg_buf[i] < '~')
        {
          beg_buf[i]++;
          break;
        }
        beg_buf[i] = ' ';
      }
    }

    end_len = pw_len - 32;

    memset(end_buf, 0, end_len);
    int i = 0;
    for (; i < end_len; ++i)
    {
      end_buf[i] = ' ';
    }
    end_buf[i++] = '\n';
    end_buf[i] = 0;

    while (true)
    {
      if (check_bytes_16_to_19(mid_buf, end_buf, pw_len))
      {
        printf("%s", create_password(beg_buf, mid_buf, end_buf, pw_buf));
        fflush(stdout);
        return;
      }

    int i;
    for (i = 4; i--;)
      {
        if (mid_buf[i] < '~')
        {
          mid_buf[i]++;
          break;
        }
        mid_buf[i] = ' ';
      }


      if (i < 0)
      {
        int iter_end = 4;
        int iter_start = end_len >= 8 ? 8 : end_len;

        for (i = iter_start; i-- > iter_end;)
        {
          if (end_buf[i] < '~')
          {
            end_buf[i]++;
            break;
          }
          end_buf[i] = ' ';
        }
      }
    }
  }
  return;
}

int main(int argc, const char **argv)
{
  char pw_buf[PW_LEN_MAX + 1];

  password_lookup(pw_buf);
}