#ifndef IMAGE_FRAMES_SAVER_GIF_H
#define IMAGE_FRAMES_SAVER_GIF_H

#include "core/io/resource_saver.h"
#include "image_frames.h"
#include "core/os/file_access.h"

class ImageFramesSaverGIF : public ResourceFormatSaver {
    //bool _gif_write(const char* fileName);
public:
    static Error save_gif(const String &p_path, const Ref<ImageFrames> &r_image_frames);
    static PoolVector<uint8_t> save_gif_to_buffer(const Ref<ImageFrames> &r_image_frames);

    ImageFramesSaverGIF();
};

#endif // IMAGE_FRAMES_SAVER_GIF_H
