#ifdef GAMECUBE

#include <aesndlib.h>
#include <stddef.h>

/*
 * Compatibility shim for AESND_AllocateVoiceWithArg, which was removed in
 * libogc2. libSDL2 for OGC was built against the old libogc and calls this
 * symbol. We implement it here using the existing AllocateVoice and
 * SetVoiceUserData APIs.
 */

typedef void (*AESNDVoiceCallbackArg)(AESNDPB *pb, u32 state, void *cbArg);

typedef struct {
    AESNDVoiceCallbackArg cb;
    void *cbArg;
    int used;
} VoiceCallbackEntry;

#define AESND_COMPAT_MAX_VOICES 16
static VoiceCallbackEntry s_voice_entries[AESND_COMPAT_MAX_VOICES];

static void compat_voice_callback(AESNDPB *pb, u32 state) {
    VoiceCallbackEntry *entry = (VoiceCallbackEntry *)AESND_GetVoiceUserData(pb);
    if (entry && entry->cb)
        entry->cb(pb, state, entry->cbArg);
}

/*
 * AESND_SetVoiceFrequency ABI shim.
 * libogc:  void AESND_SetVoiceFrequency(AESNDPB*, f32)
 * libogc2: void AESND_SetVoiceFrequency(AESNDPB*, u32)
 * libSDL2.a was compiled against the old API, so we wrap the call and
 * convert the float argument to u32 before forwarding to libogc2.
 */
void __real_AESND_SetVoiceFrequency(AESNDPB *pb, u32 freq);

void __wrap_AESND_SetVoiceFrequency(AESNDPB *pb, f32 freq) {
    __real_AESND_SetVoiceFrequency(pb, (u32)freq);
}

AESNDPB *AESND_AllocateVoiceWithArg(AESNDVoiceCallbackArg cb, void *cbArg) {
    int i;
    for (i = 0; i < AESND_COMPAT_MAX_VOICES; i++) {
        if (!s_voice_entries[i].used)
            break;
    }
    if (i == AESND_COMPAT_MAX_VOICES)
        return NULL;

    s_voice_entries[i].cb    = cb;
    s_voice_entries[i].cbArg = cbArg;
    s_voice_entries[i].used  = 1;

    AESNDPB *pb = AESND_AllocateVoice(compat_voice_callback);
    if (!pb) {
        s_voice_entries[i].used = 0;
        return NULL;
    }

    AESND_SetVoiceUserData(pb, &s_voice_entries[i]);
    return pb;
}

#endif
