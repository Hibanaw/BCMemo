import struct
import cv2
import platform

m = {
    0x000000:0,
    0x800000:1,
    0x008000:2,
    0x808000:3,
    0x000080:4,
    0x800080:5,
    0x008080:6,
    0xc0c0c0:7,
    0xc0dcc0:8,
    0xa6caf0:9,
    0x2a3faa:10,
    0x2a3fff:11,
    0x2a5f00:12,
    0x2a5f55:13,
    0x2a5faa:14,
    0x2a5fff:15,
    0x2a7f00:16,
    0x2a7f55:17,
    0x2a7faa:18,
    0x2a7fff:19,
    0x2a9f00:20,
    0x2a9f55:21,
    0x2a9faa:22,
    0x2a9fff:23,
    0x2abf00:24,
    0x2abf55:25,
    0x2abfaa:26,
    0x2abfff:27,
    0x2adf00:28,
    0x2adf55:29,
    0x2adfaa:30,
    0x2adfff:31,
    0x2aff00:32,
    0x2aff55:33,
    0x2affaa:34,
    0x2affff:35,
    0x550000:36,
    0x550055:37,
    0x5500aa:38,
    0x5500ff:39,
    0x551f00:40,
    0x551f55:41,
    0x551faa:42,
    0x551fff:43,
    0x553f00:44,
    0x553f55:45,
    0x553faa:46,
    0x553fff:47,
    0x555f00:48,
    0x555f55:49,
    0x555faa:50,
    0x555fff:51,
    0x557f00:52,
    0x557f55:53,
    0x557faa:54,
    0x557fff:55,
    0x559f00:56,
    0x559f55:57,
    0x559faa:58,
    0x559fff:59,
    0x55bf00:60,
    0x55bf55:61,
    0x55bfaa:62,
    0x55bfff:63,
    0x55df00:64,
    0x55df55:65,
    0x55dfaa:66,
    0x55dfff:67,
    0x55ff00:68,
    0x55ff55:69,
    0x55ffaa:70,
    0x55ffff:71,
    0x7f0000:72,
    0x7f0055:73,
    0x7f00aa:74,
    0x7f00ff:75,
    0x7f1f00:76,
    0x7f1f55:77,
    0x7f1faa:78,
    0x7f1fff:79,
    0x7f3f00:80,
    0x7f3f55:81,
    0x7f3faa:82,
    0x7f3fff:83,
    0x7f5f00:84,
    0x7f5f55:85,
    0x7f5faa:86,
    0x7f5fff:87,
    0x7f7f00:88,
    0x7f7f55:89,
    0x7f7faa:90,
    0x7f7fff:91,
    0x7f9f00:92,
    0x7f9f55:93,
    0x7f9faa:94,
    0x7f9fff:95,
    0x7fbf00:96,
    0x7fbf55:97,
    0x7fbfaa:98,
    0x7fbfff:99,
    0x7fdf00:100,
    0x7fdf55:101,
    0x7fdfaa:102,
    0x7fdfff:103,
    0x7fff00:104,
    0x7fff55:105,
    0x7fffaa:106,
    0x7fffff:107,
    0xaa0000:108,
    0xaa0055:109,
    0xaa00aa:110,
    0xaa00ff:111,
    0xaa1f00:112,
    0xaa1f55:113,
    0xaa1faa:114,
    0xaa1fff:115,
    0xaa3f00:116,
    0xaa3f55:117,
    0xaa3faa:118,
    0xaa3fff:119,
    0xaa5f00:120,
    0xaa5f55:121,
    0xaa5faa:122,
    0xaa5fff:123,
    0xaa7f00:124,
    0xaa7f55:125,
    0xaa7faa:126,
    0xaa7fff:127,
    0xaa9f00:128,
    0xaa9f55:129,
    0xaa9faa:130,
    0xaa9fff:131,
    0xaabf00:132,
    0xaabf55:133,
    0xaabfaa:134,
    0xaabfff:135,
    0xaadf00:136,
    0xaadf55:137,
    0xaadfaa:138,
    0xaadfff:139,
    0xaaff00:140,
    0xaaff55:141,
    0xaaffaa:142,
    0xaaffff:143,
    0xd40000:144,
    0xd40055:145,
    0xd400aa:146,
    0xd400ff:147,
    0xd41f00:148,
    0xd41f55:149,
    0xd41faa:150,
    0xd41fff:151,
    0xd43f00:152,
    0xd43f55:153,
    0xd43faa:154,
    0xd43fff:155,
    0xd45f00:156,
    0xd45f55:157,
    0xd45faa:158,
    0xd45fff:159,
    0xd47f00:160,
    0xd47f55:161,
    0xd47faa:162,
    0xd47fff:163,
    0xd49f00:164,
    0xd49f55:165,
    0xd49faa:166,
    0xd49fff:167,
    0xd4bf00:168,
    0xd4bf55:169,
    0xd4bfaa:170,
    0xd4bfff:171,
    0xd4df00:172,
    0xd4df55:173,
    0xd4dfaa:174,
    0xd4dfff:175,
    0xd4ff00:176,
    0xd4ff55:177,
    0xd4ffaa:178,
    0xd4ffff:179,
    0xff0055:180,
    0xff00aa:181,
    0xff1f00:182,
    0xff1f55:183,
    0xff1faa:184,
    0xff1fff:185,
    0xff3f00:186,
    0xff3f55:187,
    0xff3faa:188,
    0xff3fff:189,
    0xff5f00:190,
    0xff5f55:191,
    0xff5faa:192,
    0xff5fff:193,
    0xff7f00:194,
    0xff7f55:195,
    0xff7faa:196,
    0xff7fff:197,
    0xff9f00:198,
    0xff9f55:199,
    0xff9faa:200,
    0xff9fff:201,
    0xffbf00:202,
    0xffbf55:203,
    0xffbfaa:204,
    0xffbfff:205,
    0xffdf00:206,
    0xffdf55:207,
    0xffdfaa:208,
    0xffdfff:209,
    0xffff55:210,
    0xffffaa:211,
    0xccccff:212,
    0xffccff:213,
    0x33ffff:214,
    0x66ffff:215,
    0x99ffff:216,
    0xccffff:217,
    0x007f00:218,
    0x007f55:219,
    0x007faa:220,
    0x007fff:221,
    0x009f00:222,
    0x009f55:223,
    0x009faa:224,
    0x009fff:225,
    0x00bf00:226,
    0x00bf55:227,
    0x00bfaa:228,
    0x00bfff:229,
    0x00df00:230,
    0x00df55:231,
    0x00dfaa:232,
    0x00dfff:233,
    0x00ff55:234,
    0x00ffaa:235,
    0x2a0000:236,
    0x2a0055:237,
    0x2a00aa:238,
    0x2a00ff:239,
    0x2a1f00:240,
    0x2a1f55:241,
    0x2a1faa:242,
    0x2a1fff:243,
    0x2a3f00:244,
    0x2a3f55:245,
    0xfffbf0:246,
    0xa0a0a4:247,
    0x808080:248,
    0xff0000:249,
    0x00ff00:250,
    0xffff00:251,
    0x0000ff:252,
    0xff00ff:253,
    0x00ffff:254,
    0xffffff:255,
}

def RGB2Hex(r, g, b):
    h = 0
    h += r << 16
    h += g << 8
    h += b
    return h

def Hex2Code(h):
    return m[h]

if __name__ == '__main__':
    infilename = input()
    outfilename = infilename+'.bin'
    image = cv2.imread(infilename)
    size = image.shape
    #print(size)
    h = size[0]
    w = size[1]
    with open(outfilename, mode='wb') as outfile:
        bt = struct.pack("2h", w, h)
        outfile.write(bt)
        for i in range(h):
            for j in range(w):
                pixelcolor = image[i, j]
                
                r = pixelcolor[2]
                g = pixelcolor[1]
                b = pixelcolor[0]
                #print(r,g,b)
                h = RGB2Hex(r, g, b)
                #print(h)
                try:
                    c = Hex2Code(h)
                    bt = struct.pack('B', c)
                except:
                    print("[error] not a Windows standard 8 bit bitmap:")
                    print(f"color rgb={[r, g, b]} do not exist in the palette")
                    print("try ms paint to convert the image once")
                    exit(1)
                #print(c)
                
                outfile.write(bt)
    outfile.close()
    print("OK")
