#include "Sand.h"

Sand::Sand(Vector2i position) : MovableSolid(position), Solid(position), Element(position)
{
	tag = ElementTag::SAND;
}
