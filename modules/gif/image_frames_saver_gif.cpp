#include "image_frames_saver_gif.h"

#include "image_frames.h"
#include "scene/resources/texture.h"
#include "thirdparty/giflib/gif_lib.h"


int writeFromFile(GifFileType *gif, const GifByteType *data, int length) {
	// FileAccess *f = (FileAccess *)(gif->UserData); // gif->UserData is the first parameter passed to DGifOpen.
	// f->store_buffer(data, length);
    // return length;
    return 16;
}

// GifFileType* _open(void *source) {
// 	int err = 0;
// 	GifFileType* gifFile = EGifOpen(source, writeFromFile, &err);
// 	return gifFile;
// }

static bool _gif_write(FileAccess *f)
{
    int error;
    GifFileType* gifFile = EGifOpen(f, writeFromFile, &error);
    if (!gifFile) {
        ERR_PRINTS("Error opening file.");
        return false;
    }

    GifColorType colors[64];
    GifColorType* c = colors;
    int level[4] = { 0, 85, 170, 255 };
    for (int r = 0; r < 4; ++r) {
        for (int g = 0; g < 4; ++g) {
            for (int b = 0; b < 4; ++b, ++c) {
                c->Red   = level[r];
                c->Green = level[g];
                c->Blue  = level[b];
            }
        }
    }
    GifByteType pix[16] = {
        0,  1,  2,  3,  // B
        0,  4,  8, 12,  // G
        0, 16, 32, 48,  // R
        0, 21, 42, 63,  // BK
    };

    gifFile->SWidth = 4;
    gifFile->SHeight = 4;
    gifFile->SColorResolution = 8;
    gifFile->SBackGroundColor = 0;
    gifFile->SColorMap = GifMakeMapObject(64, colors);

    SavedImage gifImage;
    gifImage.ImageDesc.Left = 0;
    gifImage.ImageDesc.Top = 0;
    gifImage.ImageDesc.Width = 4;
    gifImage.ImageDesc.Height = 4;
    gifImage.ImageDesc.Interlace = false;
    gifImage.ImageDesc.ColorMap = nullptr;
    gifImage.RasterBits = (GifByteType*)malloc(16);
    gifImage.ExtensionBlockCount = 0;
    gifImage.ExtensionBlocks = nullptr;
    memcpy(gifImage.RasterBits, pix, 16);

    GifMakeSavedImage(gifFile, &gifImage);

    if (EGifSpew(gifFile) == GIF_ERROR) {
        ERR_PRINTS("Error saving file ''.");
        EGifCloseFile(gifFile, &error);
        return false;
    }

    EGifCloseFile(gifFile, &error);
    return true;
}

static Error _save_gif(Ref<ImageFrames> &r_image_frames, const Variant &source) {
	if (source.get_type() == Variant::STRING) {
		Error err;
        FileAccess *f = FileAccess::open(source, FileAccess::WRITE, &err);
		if (!f) {
			ERR_PRINTS("Error opening file '" + String(source) + "'.");
			return err;
		}
		//_gif_write(f);
        f->close();
		memdelete(f);
		return err;
	} else {
        return OK;
		//return gif.load_from_buffer(r_image_frames, source, max_frames);
	}
}

Error ImageFramesSaverGIF::save_gif(const String &p_path, const Ref<ImageFrames> &r_image_frames) {

	PoolVector<uint8_t> buffer;
    Error err = OK;
	FileAccess *file = FileAccess::open(p_path, FileAccess::WRITE, &err);
	ERR_FAIL_COND_V_MSG(err, err, vformat("Can't save GIF at path: '%s'.", p_path));

	PoolVector<uint8_t>::Read reader = buffer.read();

	//file->store_buffer(reader.ptr(), buffer.size());
    _gif_write(file);
	if (file->get_error() != OK && file->get_error() != ERR_FILE_EOF) {
		memdelete(file);
		return ERR_CANT_CREATE;
	}

	file->close();
	memdelete(file);

	return OK;
}

PoolVector<uint8_t> ImageFramesSaverGIF::save_gif_to_buffer(const Ref<ImageFrames> &r_image_frames) {

    PoolVector<uint8_t> buffer;
	return buffer;
}

ImageFramesSaverGIF::ImageFramesSaverGIF() {
	ImageFrames::save_gif_func = &save_gif;
    ImageFrames::save_gif_to_buffer_func = &save_gif_to_buffer;
}
