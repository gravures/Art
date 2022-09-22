/* X3F_IO.H
 *
 * Library for accessing X3F Files.
 *
 * Copyright 2015 - Roland and Erik Karlsson
 * BSD-style - see doc/copyright.txt
 *
 */

/* NOTE about endianess. We assume that the X3F file is little
 * endian. All multi byte (eg uint32) elements are stored in the
 * native endian of the machine. Byte streams are stored as found in
 * the file, i.e. little endian. Multi byte streams are stored each
 * multi byte element in the native endian - but the stream is stored
 * little endian. */

#ifndef X3F_IO_H
#define X3F_IO_H

#include <cinttypes> 
#include <cstdlib>

#include "x3f_printf.h"

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::size_t;

#include "../myfile.h" //include <cstdio>
//using std::FILE;
//using std::getc;
//using std::fread;

using std::realloc;

namespace x3ftools{
    
constexpr int SIZE_UNIQUE_IDENTIFIER = 16;
constexpr int SIZE_WHITE_BALANCE = 32;
constexpr int SIZE_COLOR_MODE = 32;
constexpr int NUM_EXT_DATA_2_1 = 32;
constexpr int NUM_EXT_DATA_3_0 = 64;
constexpr int NUM_EXT_DATA = NUM_EXT_DATA_3_0;

inline constexpr uint32_t X3F_VERSION(int MAJ,int MIN){ return (uint32_t)(MAJ<<16) + MIN;}
constexpr uint32_t X3F_VERSION_2_0 = X3F_VERSION(2,0);
constexpr uint32_t X3F_VERSION_2_1 = X3F_VERSION(2,1);
constexpr uint32_t X3F_VERSION_2_2 = X3F_VERSION(2,2);
constexpr uint32_t X3F_VERSION_2_3 = X3F_VERSION(2,3);
constexpr uint32_t X3F_VERSION_3_0 = X3F_VERSION(3,0);
constexpr uint32_t X3F_VERSION_4_0 = X3F_VERSION(4,0);
constexpr uint32_t X3F_VERSION_4_1 = X3F_VERSION(4,1);


/* Main file identifier */
constexpr uint32_t X3F_FOVb = (0x62564f46);
/* Directory identifier */
constexpr uint32_t X3F_SECd = (0x64434553);
/* Property section identifiers */
constexpr uint32_t X3F_PROP = (0x504f5250);
constexpr uint32_t X3F_SECp = (0x70434553);
/* Image section identifiers */
constexpr uint32_t X3F_IMAG = (0x46414d49);
constexpr uint32_t X3F_IMA2 = (0x32414d49);
constexpr uint32_t X3F_SECi = (0x69434553);
/* CAMF section identifiers */
constexpr uint32_t X3F_CAMF = (0x464d4143);
constexpr uint32_t X3F_SECc = (0x63434553);
/* CAMF entry identifiers */
constexpr uint32_t X3F_CMbP = (0x50624d43);
constexpr uint32_t X3F_CMbT = (0x54624d43);
constexpr uint32_t X3F_CMbM = (0x4d624d43);
constexpr uint32_t X3F_CMb  = (0x00624d43);
/* SDQ section identifiers ? - TODO */
constexpr uint32_t X3F_SPPA = (0x41505053);
constexpr uint32_t X3F_SECs = (0x73434553);


constexpr uint32_t X3F_IMAGE_THUMB_PLAIN       = (0x00020003);
constexpr uint32_t X3F_IMAGE_THUMB_HUFFMAN     = (0x0002000b);
constexpr uint32_t X3F_IMAGE_THUMB_JPEG        = (0x00020012);
constexpr uint32_t X3F_IMAGE_THUMB_SDQ         = (0x00020019);  /* SDQ ? - TODO */

constexpr uint32_t X3F_IMAGE_RAW_HUFFMAN_X530  = (0x00030005);
constexpr uint32_t X3F_IMAGE_RAW_HUFFMAN_10BIT = (0x00030006);
constexpr uint32_t X3F_IMAGE_RAW_TRUE          = (0x0003001e);
constexpr uint32_t X3F_IMAGE_RAW_MERRILL       = (0x0001001e);
constexpr uint32_t X3F_IMAGE_RAW_QUATTRO       = (0x00010023);
constexpr uint32_t X3F_IMAGE_RAW_SDQ           = (0x00010025);
constexpr uint32_t X3F_IMAGE_RAW_SDQH          = (0x00010027);


constexpr int X3F_IMAGE_HEADER_SIZE = 28;
constexpr int X3F_CAMF_HEADER_SIZE = 28;
constexpr int X3F_PROPERTY_LIST_HEADER_SIZE = 24;


constexpr uint32_t X3F_CAMERAID_DP1M           = 77;
constexpr uint32_t X3F_CAMERAID_DP2M           = 78;
constexpr uint32_t X3F_CAMERAID_DP3M           = 78;
constexpr uint32_t X3F_CAMERAID_DP0Q           = 83;
constexpr uint32_t X3F_CAMERAID_DP1Q           = 80;
constexpr uint32_t X3F_CAMERAID_DP2Q           = 81;
constexpr uint32_t X3F_CAMERAID_DP3Q           = 82;
constexpr uint32_t X3F_CAMERAID_SDQ            = 40;
constexpr uint32_t X3F_CAMERAID_SDQH           = 41;


typedef uint16_t utf16_t;
typedef int bool_t;


typedef enum x3f_extended_types_e{
    X3F_EXT_TYPE_NONE=0,
    X3F_EXT_TYPE_EXPOSURE_ADJUST=1,
    X3F_EXT_TYPE_CONTRAST_ADJUST=2,
    X3F_EXT_TYPE_SHADOW_ADJUST=3,
    X3F_EXT_TYPE_HIGHLIGHT_ADJUST=4,
    X3F_EXT_TYPE_SATURATION_ADJUST=5,
    X3F_EXT_TYPE_SHARPNESS_ADJUST=6,
    X3F_EXT_TYPE_RED_ADJUST=7,
    X3F_EXT_TYPE_GREEN_ADJUST=8,
    X3F_EXT_TYPE_BLUE_ADJUST=9,
    X3F_EXT_TYPE_FILL_LIGHT_ADJUST=10
}x3f_extended_types_t;


typedef struct x3f_property_s{
    /* Read from file */
    uint32_t name_offset;
    uint32_t value_offset;
    /* Computed */
    utf16_t *name;		/* 0x0000 terminated UTF 16 */
    utf16_t *value;     /* 0x0000 terminated UTF 16 */
    char *name_utf8;	/* converted to UTF 8 */
    char *value_utf8;   /* converted to UTF 8 */
}x3f_property_t;


typedef struct x3f_property_table_s{
    uint32_t size;
    x3f_property_t *element;
}x3f_property_table_t;


typedef struct x3f_property_list_s{
    /* 2.0 Fields */
    uint32_t num_properties;
    uint32_t character_format;
    uint32_t reserved;
    uint32_t total_length;

    x3f_property_table_t property_table;
    void *data;
    uint32_t data_size;
}x3f_property_list_t;


typedef struct x3f_table8_s{
    uint32_t size;
    uint8_t *element;
}x3f_table8_t;


typedef struct x3f_table16_s{
    uint32_t size;
    uint16_t *element;
}x3f_table16_t;


typedef struct x3f_table32_s{
    uint32_t size;
    uint32_t *element;
}x3f_table32_t;


typedef struct{
    uint8_t *data;		/* Pointer to actual image data */
    void *buf;			/* Pointer to allocated buffer for free() */
    uint32_t rows;
    uint32_t columns;
    uint32_t channels;
    uint32_t row_stride;
}x3f_area8_t;


typedef struct{
    uint16_t *data;		/* Pointer to actual image data */
    void *buf;			/* Pointer to allocated buffer for free() */
    uint32_t rows;
    uint32_t columns;
    uint32_t channels;
    uint32_t row_stride;
}x3f_area16_t;


constexpr uint32_t UNDEFINED_LEAF = 0xffffffff;


typedef struct x3f_huffnode_s{
    struct x3f_huffnode_s *branch[2];
    uint32_t leaf;
}x3f_huffnode_t;


typedef struct x3f_hufftree_s{
    uint32_t free_node_index; /* Free node index in huffman tree array */
    x3f_huffnode_t *nodes;    /* Coding tree */
}x3f_hufftree_t;


typedef struct x3f_true_huffman_element_s{
    uint8_t code_size;
    uint8_t code;
}x3f_true_huffman_element_t;


typedef struct x3f_true_huffman_s{
    uint32_t size;
    x3f_true_huffman_element_t *element;
}x3f_true_huffman_t;


/* 0=bottom, 1=middle, 2=top */
constexpr uint32_t TRUE_PLANES = 3;


typedef struct x3f_true_s{
    uint16_t seed[TRUE_PLANES];	/* Always 512,512,512 */
    uint16_t unknown;		    /* Always 0 */
    x3f_true_huffman_t table;	/* Huffman table - zero
                                 * terminated. size is the number of
                                 * leaves plus 1.*/
    x3f_table32_t plane_size;	/* Size of the 3 planes */
    uint8_t *plane_address[TRUE_PLANES]; /* computed offset to the planes */
    x3f_hufftree_t tree;		/* Coding tree */
    x3f_area16_t x3rgb16;		/* 3x16 bit X3-RGB data */
}x3f_true_t;


typedef struct x3f_quattro_s{
    struct{
        uint16_t columns;
        uint16_t rows;
    }plane[TRUE_PLANES];
    uint32_t unknown;
    bool_t quattro_layout;
    x3f_area16_t top16;		/* Container for the bigger top layer */
}x3f_quattro_t;


typedef struct x3f_huffman_s{
    x3f_table16_t mapping;     /* Value Mapping = X3F lossy compression */
    x3f_table32_t table;       /* Coding Table */
    x3f_hufftree_t tree;	   /* Coding tree */
    x3f_table32_t row_offsets; /* Row offsets */
    x3f_area8_t rgb8;		   /* 3x8 bit RGB data */
    x3f_area16_t x3rgb16;	   /* 3x16 bit X3-RGB data */
}x3f_huffman_t;


typedef struct x3f_image_data_s{
    /* 2.0 Fields 
     * ------------------------------------------------------------------
     * Known combinations of type and format are:
     * 1-6, 2-3, 2-11, 2-18, 3-6                    */
    uint32_t _type;                /* 1 = RAW X3 (SD1)
                                     2 = thumbnail or maybe just RGB
                                     3 = RAW X3 */
    uint32_t format;              /* 3 = 3x8 bit pixmap
                                     6 = 3x10 bit huffman with map table
                                     11 = 3x8 bit huffman
                                     18 = JPEG */
    uint32_t type_format;         /* type<<16 + format */
    /* ------------------------------------------------------------------ */
    uint32_t columns;             /* width / row size in pixels */
    uint32_t rows;                /* height */
    uint32_t row_stride;          /* row size in bytes */

    /* nullptr if not used */
    x3f_huffman_t *huffman;     /* Huffman help data */
    x3f_true_t *tru;		    /* TRUE help data */
    x3f_quattro_t *quattro;	    /* Quattro help data */

    void *data;                 /* Take from file if nullptr. Otherwise,
                                 * this is the actual data bytes in
                                 * the file. */
    uint32_t data_size;
}x3f_image_data_t;


typedef struct camf_dim_entry_s{
    uint32_t size;
    uint32_t name_offset;
    uint32_t n;  /* 0,1,2,3... */
    char *name;
}camf_dim_entry_t;


typedef enum{
    M_FLOAT, 
    M_INT, 
    M_UINT
}matrix_type_t;


typedef struct camf_entry_s{
    /* pointer into decoded data */
    void *entry;
   
    /* entry header */
    uint32_t id;
    uint32_t version;
    uint32_t entry_size;
    uint32_t name_offset;
    uint32_t value_offset;

    /* computed values */
    char *name_address;
    void *value_address;
    uint32_t name_size;
    uint32_t value_size;

    /* extracted values for explicit CAMF entry types*/
    uint32_t text_size;
    char *text;

    uint32_t property_num;
    char **property_name;
    uint8_t **property_value;

    uint32_t matrix_dim;
    camf_dim_entry_t *matrix_dim_entry;

    /* Offset, pointer and size and type of raw data */
    uint32_t matrix_type;
    uint32_t matrix_data_off;
    void *matrix_data;
    uint32_t matrix_element_size;

    /* Pointer and type of copied data */
    matrix_type_t matrix_decoded_type;
    void *matrix_decoded;

    /* Help data to try to estimate element size */
    uint32_t matrix_elements;
    uint32_t matrix_used_space;
    double matrix_estimated_element_size;
}camf_entry_t;


typedef struct camf_entry_table_s{
    uint32_t size;
    camf_entry_t *element;
}camf_entry_table_t;


typedef struct x3f_camf_typeN_s{
    uint32_t val0;
    uint32_t val1;
    uint32_t val2;
    uint32_t val3;
}x3f_camf_typeN_t;


typedef struct x3f_camf_type2_s{
    uint32_t reserved;
    uint32_t infotype;
    uint32_t infotype_version;
    uint32_t crypt_key;
}x3f_camf_type2_t;


typedef struct x3f_camf_type4_s{
    uint32_t decoded_data_size;
    uint32_t decode_bias;
    uint32_t block_size;
    uint32_t block_count;
}x3f_camf_type4_t;


typedef struct x3f_camf_type5_s{
    uint32_t decoded_data_size;
    uint32_t decode_bias;
    uint32_t unknown2;
    uint32_t unknown3;
}x3f_camf_type5_t;


typedef struct x3f_camf_s{
    /* Header info */
    uint32_t _type;
    union{
        x3f_camf_typeN_t tN;
        x3f_camf_type2_t t2;
        x3f_camf_type4_t t4;
        x3f_camf_type5_t t5;
    };

    /* The encrypted raw data */
    void *data;
    uint32_t data_size;

    /* Help data for type 4 Huffman compression */
    x3f_true_huffman_t table;
    x3f_hufftree_t tree;
    uint8_t *decoding_start;
    uint32_t decoding_size;

    /* The decrypted data */
    void *decoded_data;
    uint32_t decoded_data_size;

    /* Pointers into the decrypted data */
    camf_entry_table_t entry_table;
}x3f_camf_t;


typedef struct x3f_directory_entry_header_s{
    uint32_t identifier;        /* Should be ´SECp´, "SECi", ... */
    uint32_t version;           /* 0x00020001 is version 2.1  */
    union{
        x3f_property_list_t property_list;
        x3f_image_data_t image_data;
        x3f_camf_t camf;
    }data_subsection;
}x3f_directory_entry_header_t;


typedef struct x3f_directory_entry_s{
    struct{
        uint32_t offset;
        uint32_t size;
    }input, output;
    uint32_t _type;
    x3f_directory_entry_header_t header;
}x3f_directory_entry_t;


typedef struct x3f_directory_section_s{
    uint32_t identifier;          /* Should be ´SECd´ */
    uint32_t version;             /* 0x00020001 is version 2.1  */

    /* 2.0 Fields */
    uint32_t num_directory_entries;
    x3f_directory_entry_t *directory_entry;
}x3f_directory_section_t;


typedef struct x3f_header_s{
    /* 2.0 Fields */
    uint32_t identifier;          /* Should be ´FOVb´ */
    uint32_t version;             /* 0x00020001 means 2.1 */
    uint8_t unique_identifier[SIZE_UNIQUE_IDENTIFIER];
    uint32_t mark_bits;
    uint32_t columns;             /* Columns and rows ... */
    uint32_t rows;                /* ... before rotation */
    uint32_t rotation;            /* 0, 90, 180, 270 */

    char white_balance[SIZE_WHITE_BALANCE]; /* Introduced in 2.1 */
    char color_mode[SIZE_COLOR_MODE];       /* Introduced in 2.3 */

    /* Introduced in 2.1 and extended from 32 to 64 in 3.0 */
    uint8_t extended_types[NUM_EXT_DATA]; /* x3f_extended_types_t */
    float extended_data[NUM_EXT_DATA]; /* 32 bits, but do type differ? */
}x3f_header_t;


typedef struct x3f_info_s{
    const char *error;
    struct{
        IMFILE *file; /* Use if more data is needed */
        // FILE *file;
    }input, output;
}x3f_info_t;


typedef struct x3f_s{
    x3f_info_t info;
    x3f_header_t header;
    x3f_directory_section_t directory_section;
}x3f_t;


typedef enum x3f_return_e{
    X3F_OK=0,
    X3F_ARGUMENT_ERROR=1,
    X3F_INFILE_ERROR=2,
    X3F_OUTFILE_ERROR=3,
    X3F_INTERNAL_ERROR=4
}x3f_return_t;

/* --------------------------------------------------------------------- */
/* Reading and writing - assuming little endian in the file              */
/* --------------------------------------------------------------------- */
static int x3f_get1(IMFILE *f){ /* Little endian file */
    return getc(f);
}

static int x3f_get2(IMFILE *f){ /* Little endian file */
    return (getc(f)<<0) + (getc(f)<<8);
}

static int x3f_get4(IMFILE *f){ /* Little endian file */
    return (getc(f)<<0) + (getc(f)<<8) + (getc(f)<<16) + (getc(f)<<24);
}

template<typename S> 
inline void GETN(void *buffer, S size, x3f_info_t *info){
    size_t left = size;
    while (left!=0){
        size_t cur = fread(buffer, 1, left, info->input.file);
        if (cur==0){
            x3f_printf(ERR, "Failure to access file\n");
            exit(1);
        }
        left -= cur;
    }
}

template<typename T>
inline void GET1(T *v, x3f_info_t *I){
    *v = x3f_get1(I->input.file);
}

template<typename T>
inline void GET2(T *v, x3f_info_t *I){
    *v = x3f_get2(I->input.file);
}    

template<typename T>
inline void GET4(T *v, x3f_info_t *I){
    *v = x3f_get4(I->input.file);
}

template<typename T>
inline void GET4F(T *v, x3f_info_t *I){
    union {int32_t i; float f;} tmp;
    tmp.i = x3f_get4(I->input.file);
    *v = tmp.f;
}

template<typename T>
inline void GET_TABLE_16(T& TABLE, int NUM, x3f_info_t *I){
    int i;
    TABLE.size = NUM;
    TABLE.element = static_cast<uint16_t  *>(realloc(TABLE.element, NUM * sizeof(TABLE.element[0])));
    for (i = 0; i<TABLE.size; i++)
        GET2(&TABLE.element[i], I);
}

template<typename T>
inline void GET_TABLE_32(T& TABLE, int NUM, x3f_info_t *I){
    int i;
    TABLE.size = NUM;
    TABLE.element = static_cast<uint32_t *>(realloc(TABLE.element, NUM * sizeof(TABLE.element[0])));
    for (i = 0; i<TABLE.size; i++)
        GET4(&TABLE.element[i], I);
}

extern int legacy_offset;
extern bool_t auto_legacy_offset;
extern x3f_t *x3f_new_from_file(IMFILE *infile);
extern x3f_return_t x3f_delete(x3f_t *x3f);
extern x3f_directory_entry_t *x3f_get_raw(x3f_t *x3f);
extern x3f_directory_entry_t *x3f_get_thumb_plain(x3f_t *x3f);
extern x3f_directory_entry_t *x3f_get_thumb_huffman(x3f_t *x3f);
extern x3f_directory_entry_t *x3f_get_thumb_jpeg(x3f_t *x3f);
extern x3f_directory_entry_t *x3f_get_camf(x3f_t *x3f);
extern x3f_directory_entry_t *x3f_get_prop(x3f_t *x3f);
extern x3f_return_t x3f_load_data(x3f_t *x3f, x3f_directory_entry_t *DE);
extern x3f_return_t x3f_load_image_block(x3f_t *x3f, x3f_directory_entry_t *DE);
const extern char *x3f_err(x3f_return_t err);


} // namespace x3ftools
#endif /* X3F_IO_H */