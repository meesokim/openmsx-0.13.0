#ifndef PNG_HH
#define PNG_HH

#include "SDLSurfacePtr.hh"
#include <string>

struct SDL_Surface;
struct SDL_PixelFormat;

namespace openmsx {

/** Utility functions to hide the complexity of saving to a PNG file.
  */
namespace PNG {
	/** Load the given PNG file in a SDL_Surface.
	 * This SDL_Surface is either 24bpp or 32bpp, depending on whether the
	 * PNG file had an alpha layer. But it's possible to force a 32bpp
	 * surface. The surface will use RGB(A) or BGR(A) format depending on
	 * the current display format.
	 */
	SDLSurfacePtr load(const std::string& filename, bool want32bpp);

	void save(SDL_Surface* image, const std::string& filename);
	void save(unsigned width, unsigned height, const void** rowPointers,
	          const SDL_PixelFormat& format, const std::string& filename);
	void save(unsigned witdh, unsigned height, const void** rowPointers,
	          const std::string& filename);
	void saveGrayscale(unsigned witdh, unsigned height,
	                   const void** rowPointers, const std::string& filename);

} // namespace PNG
} // namespace openmsx

#endif // PNG_HH
