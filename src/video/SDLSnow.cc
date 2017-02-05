#include "SDLSnow.hh"
#include "OutputSurface.hh"
#include "Display.hh"
#include "build-info.hh"
#include "random.hh"
#include <cstring>
#include <cstdint>

namespace openmsx {

template <class Pixel>
SDLSnow<Pixel>::SDLSnow(OutputSurface& output, Display& display_)
	: Layer(COVER_FULL, Z_BACKGROUND)
	, display(display_)
{
	// Precalc gray values for noise
	for (int i = 0; i < 256; ++i) {
		gray[i] = output.mapRGB255(gl::ivec3(i));
	}
}

template <class Pixel>
void SDLSnow<Pixel>::paint(OutputSurface& output)
{
	auto& generator = global_urng(); // fast (non-cryptographic) random numbers
	std::uniform_int_distribution<int> distribution(0, 255);

	output.lock();
	const unsigned width = output.getWidth();
	const unsigned height = output.getHeight();
	for (unsigned y = 0; y < height; y += 2) {
		Pixel* p0 = output.getLinePtrDirect<Pixel>(y + 0);
		Pixel* p1 = output.getLinePtrDirect<Pixel>(y + 1);
		for (unsigned x = 0; x < width; x += 2) {
			p0[x + 0] = p0[x + 1] = gray[distribution(generator)];
		}
		memcpy(p1, p0, width * sizeof(Pixel));
	}

	display.repaintDelayed(100 * 1000); // 10fps
}

// Force template instantiation.
#if HAVE_16BPP
template class SDLSnow<uint16_t>;
#endif
#if HAVE_32BPP
template class SDLSnow<uint32_t>;
#endif

} // namespace openmsx
