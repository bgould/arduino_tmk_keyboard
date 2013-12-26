#ifndef PRINT_H__
#define PRINT_H__ 1

#define print(s)                print_P(PSTR(s))
#define print_set_sendchar(func)
#define print_S(s)
#define print_P(s)
#define print_dec(data)
#define print_decs(data)
#define print_hex4(data)
#define print_hex8(data)
#define print_hex16(data)
#define print_hex32(data)
#define print_bin4(data)
#define print_bin8(data)
#define print_bin16(data)
#define print_bin32(data)
#define print_bin_reverse8(data)
#define print_bin_reverse16(data)
#define print_bin_reverse32(data)

#define pdec(data)              print_dec(data)
#define pdec16(data)            print_dec(data)
#define phex(data)              print_hex8(data)
#define phex16(data)            print_hex16(data)
#define pbin(data)              print_bin8(data)
#define pbin16(data)            print_bin16(data)
#define pbin_reverse(data)      print_bin_reverse8(data)
#define pbin_reverse16(data)    print_bin_reverse16(data)

#endif
