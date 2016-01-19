#define _GNU_SOURCE
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

#define handle_error(msg) \
do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define FLAG_LEN 46
#define MEM_ENTROPY_LEN 512
#define FIRST_MUT_LEN 286

void first_mutation(void* mem);
void second_mutation(void* mem);
void third_mutation(void* mem);
void wrong_password();

char *mem_entropy = "\x1f\x40\xfc\x92\xda\x24\x16\x94\x75\x09\x79\xee\x6c\xf5\x82\xf2\xd5\xd7\xd2\x8e\x18\x33\x5d\xe0\x5a\xbc\x54\xd0\x56\x0e\x0f\x53\x02\x86\x0c\x65\x2b\xf0\x8d\x56\x02\x52\xaa\x5e\x74\x21\x05\x46\xf3\x69\xfb\xbb\xce\x8c\x12\xcf\xc7\x95\x7b\x26\x52\xfe\x9a\x75"
        "\x52\x67\x76\x88\x22\xee\x62\x4d\x48\xfc\xe1\x5e\xc5\xca\x79\xcb\xd6\x02\xcb\x7f\x4c\x21\x57\xa5\x16\x55\x69\x91\xf2\x2e\xf8\xc7\xb5\xef\x7b\x18\xd1\xff\x41\xc5\x93\x70\xef\xb0\x85\x86\x51\xd4\x4a\x93\x6c\x11\xb7\xb1\x44\xc4\x8f\xe0\x4d\xf3\xc6\xa3\xe8\xda"
        "\xac\xc2\x8d\xb2\xbe\xb7\xb4\x2b\xaa\x1c\xb0\x24\x3d\x40\x1c\xcb\x4e\x3f\xce\x44\xd7\xb0\x28\x79\xa5\x27\x99\xaa\xdf\xf5\x41\x52\x2d\x88\x22\x59\x8b\x2f\xa6\x64\xf9\xd5\x15\x6c\x00\xc9\x24\x80\x5d\x75\xc3\x86\x8b\xd5\x6c\x2a\xcb\x81\xd3\x7e\x98\xe3\x5a\xdc"
        "\x48\xfb\x10\xb1\x5f\x3d\x44\xa0\x9d\xc8\x2d\x02\xb0\x65\x81\xe0\xc0\xc6\x94\x78\xc9\xfd\x2c\xf8\xf9\x09\x36\x59\x01\x9a\x16\x87\xba\xec\xdb\xb3\x8c\x9e\x72\xb1\x21\x69\xdc\x41\x48\x69\x0f\x87\x46\x7f\x91\x54\xf5\x93\x1c\x5d\xf6\x65\xc6\x49\x6c\xbf\xd5\xf5"
        "\x87\xc5\x68\xe0\x37\xa5\xfa\x50\xb1\xbc\x91\x1e\x8e\xe1\x9a\x77\xc4\xdd\x3c\x22\xbc\xe9\x93\x2f\x86\xfd\xd8\xa2\x16\xaf\xe1\x68\x1c\x89\x73\x7f\xad\xa6\x85\x9e\x91\x04\x7e\xec\xe7\x11\xec\x16\xda\x62\xd6\xcc\xb9\xfd\x0d\xe2\xc5\x1f\x13\x23\x47\x35\x0d\x8c"
        "\x71\x1c\x22\x44\x8e\x72\x1e\x54\x91\xd8\x24\x5b\x49\x42\x5a\xa8\x61\xf1\xfc\x4a\x15\x28\x7f\x07\x35\xe2\x03\x79\x9b\x65\xcf\xfe\xc5\x0b\x5a\xbd\x0f\xdd\xd9\x1c\xd6\x43\xae\xb3\xb5\x30\xd4\x8f\x05\xe2\x58\xe7\xe2\x30\xa9\x4e\xd5\x02\x5c\x13\x87\xbb\x4e\x1b"
        "\x19\xf1\x42\xb0\x18\xf3\x07\xbf\xdf\x1c\x70\x09\xd1\x5a\x29\x41\x7c\x96\xd8\x67\x8d\x29\x82\xee\xbc\xe4\x96\x1b\x2e\x67\xee\xb1\x18\xa8\xeb\xb1\xd7\x5b\x70\x08\x7c\x3e\x65\xbc\x79\x34\x50\xe3\xfe\x4a\x10\x00\x2b\xef\xa2\xd0\x38\xe5\xae\xd4\x79\x69\x37\xf2"
        "\x22\x41\xbc\x8f\xc7\x07\x05\xb4\x2e\xfe\xad\x37\x1f\xd4\x98\x2c\x5b\xa6\x99\x17\xe5\xb4\xb8\x95\x81\x00\x02\x64\x4f\x03\x86\xda\x9c\x31\x31\x79\x34\x58\xc2\xbf\x47\x60\x84\x80\xd6\x4a\x07\x27\x81\x33\xc9\x99\x12\xe0\xba\x2d\xaf\x23\x09\x8f\x35\x20\xeb\x97";

int valid_one(char* str) {
    return (str[0] == 'U'
        && str[1] == 'Q'
        && str[2] == 'A'
        && str[3] == 'M'
        && str[4] == '{'
        && str[5] == 'W'
        && str[6] == 'h'
        && str[7] == '3'
        && str[8] == 'r'
        && str[9] == '3'
        && str[10] == '_'
        && str[11] == 'T'
        && str[12] == 'h'
        && str[13] == '3'
        && str[14] == '_'
        && str[15] == 'H');
}

// Suffice to say that I'm not a purist
// length = 46 (16, 15 15)
// UQAM{Wh3r3_Th3_H3ck_d1d_y0u_l34rn_Pr0Gr4MM1nG}
int main(int argc, char **argv) {
	void *executable_mem = NULL;
    int fd = -1;

    if (argc != 2) {
        fprintf(stderr, "Usage : %s password", argv[0]);
        exit(-1);
    }

    if (strlen(argv[1]) != FLAG_LEN)  {
        wrong_password();
    }

	executable_mem = mmap(NULL, 512,
			PROT_EXEC | PROT_READ | PROT_WRITE, 
			MAP_PRIVATE | MAP_ANONYMOUS, fd, 0);

	if (executable_mem == MAP_FAILED) {
		handle_error("mmap");
	}

    memcpy(executable_mem, mem_entropy, MEM_ENTROPY_LEN);

    first_mutation(executable_mem);

    if (((int (*)())executable_mem)(argv[1]) != 1) {
        wrong_password();
    }

	return 0;
}

void first_mutation(void *mem) {
    char new_mem[] = {
        0x4a, 0x08, 0x75, 0x77, 0x92, 0xad, 0x6b, 0x6c, 0x3d, 0x82, 0x3c, 0x16, 0x63, 0x43, 0x82, 0xce,
        0x80, 0xd8, 0x57, 0x8e, 0x19, 0x33, 0x5d, 0xa8, 0xd1, 0xf9, 0xac, 0x98, 0xd5, 0xce, 0x0e, 0x5c,
        0xb4, 0x86, 0x30, 0x34, 0x24, 0x75, 0x60, 0x56, 0x02, 0x52, 0xe2, 0xd5, 0x31, 0xd9, 0x4d, 0xc5,
        0x33, 0x6b, 0xf4, 0x0d, 0xce, 0xb0, 0x53, 0xc0, 0x42, 0x4f, 0x7b, 0x26, 0x52, 0xb6, 0x11, 0x30,
        0xaa, 0x2f, 0xf5, 0x48, 0x21, 0xe1, 0xd4, 0x4d, 0x74, 0xb1, 0xee, 0xdb, 0x02, 0xca, 0x79, 0xcb,
        0x9e, 0x89, 0x8e, 0x87, 0x04, 0xa2, 0x97, 0xa1, 0x19, 0xe3, 0x69, 0xad, 0x89, 0x21, 0x7d, 0x73,
        0xb5, 0xef, 0x7b, 0x50, 0x5a, 0xba, 0xb9, 0x8d, 0x10, 0xb0, 0xea, 0xbf, 0x33, 0x86, 0x6d, 0x83,
        0x45, 0x16, 0xcd, 0x11, 0xb7, 0xb1, 0x0c, 0x4f, 0xca, 0x18, 0x05, 0x70, 0x06, 0xa5, 0xe7, 0x6c,
        0xac, 0xfe, 0xe5, 0xbd, 0x3b, 0x39, 0xb4, 0x2b, 0xaa, 0x54, 0x3b, 0x61, 0xc5, 0x08, 0x9f, 0x0b,
        0x49, 0x30, 0x78, 0x44, 0xeb, 0x83, 0x5d, 0x06, 0xed, 0xac, 0xdc, 0x52, 0x97, 0x76, 0x81, 0x5a,
        0x22, 0x3e, 0x22, 0x65, 0xf9, 0x5a, 0xd6, 0x2c, 0x72, 0x90, 0xed, 0x24, 0x83, 0x09, 0x2d, 0x8f,
        0xeb, 0x75, 0xff, 0xb5, 0xfe, 0xb4, 0x24, 0xa1, 0x8e, 0x79, 0x9b, 0xfd, 0x58, 0xe9, 0x55, 0x6a,
        0x48, 0xc7, 0x4f, 0xc4, 0x0d, 0x75, 0xcf, 0xe5, 0x65, 0x80, 0xae, 0xc2, 0xbb, 0x6a, 0x37, 0xe0,
        0xfc, 0x92, 0xe1, 0x3b, 0x81, 0x76, 0x69, 0x00, 0xb1, 0x8a, 0xf6, 0x55, 0x0e, 0x2c, 0x16, 0xbb,
        0xd2, 0x99, 0xef, 0xfb, 0x07, 0xdb, 0x8a, 0xf9, 0xa2, 0xa9, 0xd1, 0x4e, 0xfe, 0x69, 0x33, 0xb4,
        0x33, 0x5a, 0xd9, 0xdf, 0xb0, 0x6b, 0x54, 0xde, 0x36, 0x6b, 0xc9, 0xff, 0x6c, 0x83, 0x8a, 0x80,
        0x91, 0x8d, 0xe3, 0xa5, 0xcf, 0xed, 0x79, 0x90, 0xbe, 0xb3, 0x27, 0x1e, 0xb2, 0xa9, 0xef, 0x70,
        0x7c, 0xdc, 0x3c, 0x22, 0xbc, 0x02, 0x96, 0x97, 0x86, 0xfd, 0xd8, 0xa2, 0x4b, 0x6c
    };

    for (int i = 0; i < FIRST_MUT_LEN; ++i) {
        ((char*)mem)[i] ^= new_mem[i];
    }

}

void wrong_password() {
    puts("Wrong password !");
}