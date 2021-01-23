#include <stdio.h>
#include <stdlib.h>

// 'path' ファイルの中身を char* に格納
static char* read_file(char* path) {
    // open 'path' file
    FILE* fp;
    if ( ( fp = fopen(path, "r") ) == NULL ) {
        fprintf(stderr, "Can't open file: %s", path);
        exit(EXIT_FAILURE);
    }
    
    // バッファーへの書き込み用にストリームをオープン
    char* buf;
    size_t buflen;
    FILE* out = open_memstream(&buf, &buflen);
    
    // fp の中身をすべて out に格納
    for (;;) {
        char buf2[4096];
        int n = fread(buf2, 1, sizeof(buf2), fp);
        if (n == 0)
            break;
        fwrite(buf2, 1, n, out);
    }
    
    fclose(fp);
    
    // buf, buflen のサイズを更新
    fflush(out);
    
    if (buflen == 0 || buf[buflen - 1] != '\n')
        fputc('\n', out);
    fputc('\0', out);
    
    // buf, buflen のサイズを更新
    fclose(out);
    
    return buf;
}

int main() {
    char* source = read_file("input.txt");
    printf("%s", source);
    return 0;
}