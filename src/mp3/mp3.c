#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include "connector.h"

#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"

typedef struct {
    mp3dec_t mp3d;
    int buffer_offset;
    int buffer_remaining;
    short buffer[MINIMP3_MAX_SAMPLES_PER_FRAME];
} mp3_dec_lib;

CONNECTOR_EXPORT jlong JNICALL Java_com_sedmelluq_discord_lavaplayer_natives_mp3_Mp3DecoderLibrary_create(JNIEnv *jni, jobject me) {
    mp3_dec_lib* lib = malloc(sizeof(*lib));
    if(lib == NULL) {
        return 0;
    }
    mp3dec_init(&lib->mp3d);
    lib->buffer_offset = 0;
    lib->buffer_remaining = 0;

    return (jlong)lib;
}

CONNECTOR_EXPORT void JNICALL Java_com_sedmelluq_discord_lavaplayer_natives_mp3_Mp3DecoderLibrary_destroy(JNIEnv *jni, jobject me, jlong instance) {
    mp3_dec_lib* handle = (mp3_dec_lib*)instance;

    if(handle != NULL) {
        free(handle);
    }
}

CONNECTOR_EXPORT jint JNICALL Java_com_sedmelluq_discord_lavaplayer_natives_mp3_Mp3DecoderLibrary_decode(JNIEnv *jni, jobject me, jlong instance, jobject direct_input,
        jint input_length, jobject direct_output, jint output_length) {

    if (instance == 0) {
        return -1;
    }
    mp3_dec_lib* lib = (mp3_dec_lib*)instance;

    unsigned char* input = (*jni)->GetDirectBufferAddress(jni, direct_input);
    unsigned char* output = (*jni)->GetDirectBufferAddress(jni, direct_output);

    if(lib->buffer_remaining > 0) {
        int nbytes = output_length < lib->buffer_remaining ? output_length : lib->buffer_remaining;
        memcpy(output, &lib->buffer[lib->buffer_offset], nbytes);
        lib->buffer_offset += nbytes;
        lib->buffer_remaining -= nbytes;
        return nbytes;
    }

    mp3dec_frame_info_t info;
    if(output_length < MINIMP3_MAX_SAMPLES_PER_FRAME) {
        int nbytes = 2 * mp3dec_decode_frame(&lib->mp3d, input, input_length, &lib->buffer, &info);
        if(nbytes <= output_length) {
            memcpy(output, &lib->buffer, nbytes);
            return nbytes;
        } else {
            memcpy(output, &lib->buffer, output_length);
            lib->buffer_offset = output_length;
            lib->buffer_remaining = nbytes - output_length;
            return output_length;
        }
    } else {
        return 2 * mp3dec_decode_frame(&lib->mp3d, input, input_length, output, &info);
    }
}