#ifndef IMAGE_FRAMES_H
#define IMAGE_FRAMES_H

#include "core/image.h"

class ImageFrames;

typedef Error (*LoadImageFramesFunction)(Ref<ImageFrames> &r_image_frames, const Variant &source, int max_frames);
typedef Error (*SaveImageFramesFunction)(const String &p_path, const Ref<ImageFrames> &r_image_frames);
typedef PoolVector<uint8_t> (*SaveImageFramesToBufferFunction)(const Ref<ImageFrames> &r_image_frames);

class ImageFrames : public Resource {
	GDCLASS(ImageFrames, Resource);

	struct Frame {
		Ref<Image> image;
		float delay;
	};
	Vector<Frame> frames;

protected:
	static void _bind_methods();

public:
	static LoadImageFramesFunction load_gif_func;
	static SaveImageFramesFunction save_gif_func;
	static SaveImageFramesToBufferFunction save_gif_to_buffer_func;

	Error load(const String &p_path, int max_frames = 0);
	Error load_gif_from_buffer(const PoolByteArray &p_data, int max_frames = 0);

	Error save_gif(const String &p_path);
	PoolVector<uint8_t> save_gif_to_buffer() const;

	void add_frame(const Ref<Image> &p_image, float p_delay, int p_idx = -1);
	void remove_frame(int p_idx);

	void set_frame_image(int p_idx, const Ref<Image> &p_image);
	Ref<Image> get_frame_image(int p_idx) const;

	void set_frame_delay(int p_idx, float p_delay);
	float get_frame_delay(int p_idx) const;

	int get_frame_count() const;

	void clear();
};

#endif // IMAGE_FRAMES_H
