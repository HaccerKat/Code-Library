FILE *input_stream = fopen("run.in", "rb");
FILE *output_stream = fopen("run.out", "wb");
const int BUFFER_SIZE = 20 << 20;
char buffer[BUFFER_SIZE], *BUF = buffer;
template<class T> void scan(T &x) {
    int sign = 1;
    while (*BUF < '0' || *BUF > '9') {
        if (*BUF == '-')
            sign = -1;
        BUF++;
    }
    x = 0;
    while (*BUF >= '0' && *BUF <= '9') {
        x = (x << 1) + (x << 3) + (*BUF - '0');
        BUF++;
    }
    
    x *= sign;
}