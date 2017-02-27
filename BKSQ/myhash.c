void myhash32(uint8_t const *in, uint8_t * hash) {
    uint8_t tmp[BLOCKLEN_BYTES];
    dmhash(in, BLOCKLEN_BYTES * 8, tmp);
    int i;
    for (i = 0; i < 4; i++) {
        hash[i] = tmp[i] ^ tmp[i + 4] ^ tmp[i + 8];
    }
}

void myhash48(uint8_t const *in, uint8_t * hash) {
    uint8_t tmp[BLOCKLEN_BYTES];
    dmhash(in, BLOCKLEN_BYTES * 8, tmp);
    int i;
    for (i = 0; i < 6; i++) {
        hash[i] = tmp[i] ^ tmp[i + 6];
    }
}


