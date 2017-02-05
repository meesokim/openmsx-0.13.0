#include "RendererFactory.hh"
#include "RenderSettings.hh"
#include "Reactor.hh"
#include "Display.hh"
#include "Version.hh"
#include "memory.hh"
#include "unreachable.hh"

// Video systems:
#include "components.hh"
#include "DummyVideoSystem.hh"
#include "SDLVideoSystem.hh"

// Renderers:
#include "DummyRenderer.hh"
#include "PixelRenderer.hh"
#include "V9990DummyRenderer.hh"
#include "V9990PixelRenderer.hh"

#if COMPONENT_LASERDISC
#include "LDDummyRenderer.hh"
#include "LDPixelRenderer.hh"
#endif

using std::unique_ptr;

namespace openmsx {
namespace RendererFactory {

unique_ptr<VideoSystem> createVideoSystem(Reactor& reactor)
{
	Display& display = reactor.getDisplay();
	switch (display.getRenderSettings().getRenderer()) {
		case RenderSettings::DUMMY:
			return make_unique<DummyVideoSystem>();
		case RenderSettings::SDL:
		case RenderSettings::SDLGL_PP:
		case RenderSettings::SDLGL_FB16:
		case RenderSettings::SDLGL_FB32:
			return make_unique<SDLVideoSystem>(
				reactor, display.getCommandConsole());
		default:
			UNREACHABLE; return nullptr;
	}
}

unique_ptr<Renderer> createRenderer(VDP& vdp, Display& display)
{
	switch (display.getRenderSettings().getRenderer()) {
		case RenderSettings::DUMMY:
			return make_unique<DummyRenderer>();
		case RenderSettings::SDL:
		case RenderSettings::SDLGL_PP:
		case RenderSettings::SDLGL_FB16:
		case RenderSettings::SDLGL_FB32:
			return make_unique<PixelRenderer>(vdp, display);
		default:
			UNREACHABLE; return nullptr;
	}
}

unique_ptr<V9990Renderer> createV9990Renderer(V9990& vdp, Display& display)
{
	switch (display.getRenderSettings().getRenderer()) {
		case RenderSettings::DUMMY:
			return make_unique<V9990DummyRenderer>();
		case RenderSettings::SDL:
		case RenderSettings::SDLGL_PP:
		case RenderSettings::SDLGL_FB16:
		case RenderSettings::SDLGL_FB32:
			return make_unique<V9990PixelRenderer>(vdp);
		default:
			UNREACHABLE; return nullptr;
	}
}

#if COMPONENT_LASERDISC
unique_ptr<LDRenderer> createLDRenderer(LaserdiscPlayer& ld, Display& display)
{
	switch (display.getRenderSettings().getRenderer()) {
		case RenderSettings::DUMMY:
			return make_unique<LDDummyRenderer>();
		case RenderSettings::SDL:
		case RenderSettings::SDLGL_PP:
		case RenderSettings::SDLGL_FB16:
		case RenderSettings::SDLGL_FB32:
			return make_unique<LDPixelRenderer>(ld, display);
		default:
			UNREACHABLE; return nullptr;
	}
}
#endif

} // namespace RendererFactory
} // namespace openmsx
