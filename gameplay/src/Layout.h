#ifndef LAYOUT_H_
#define LAYOUT_H_

#include "Ref.h"
#include "Touch.h"
#include "Vector2.h"

namespace gameplay
{

class Container;
class Control;

/**
 * The layout interface for UI containers.
 *
 * Implementations of this interface are responsible for positioning, resizing
 * and then calling update on all the controls within a container.
 */
class Layout : public Ref
{
    friend class Container;
    friend class Form;

public:
    /**
     * Layout types available to containers.
     */
    enum Type
    {
        /**
         * Flow layout: Controls are placed next to one another horizontally
         * until the right-most edge of the container is reached, at which point
         * a new row is started.
         */
        LAYOUT_FLOW,

        /**
         * Vertical layout: Controls are placed next to one another vertically until
         * the bottom-most edge of the container is reached.
         */
        LAYOUT_VERTICAL,

        /**
         * Absolute layout: Controls are not modified at all by this layout.
         * They must be positioned and sized manually.
         */
        LAYOUT_ABSOLUTE,

        /**
         * Scroll layout: Controls may be placed outside the bounds of the container.
         * The user can then touch and drag to scroll.  By default controls are placed
         * based on absolute positions in the .form file, but vertical or horizontal
         * automatic positioning is an available option.
         */
        LAYOUT_SCROLL
    };

    /**
     * Get the type of this layout.
     *
     * @return The type of this layout.
     */
    virtual Type getType() = 0;

protected:
    /**
     * Position, resize, and update the controls within a container.
     *
     * @param container The container to update.
     */
    virtual void update(const Container* container, const Vector2& offset) = 0;

    /**
     * Align a control within a container.
     *
     * @param control The control to align.
     * @param container The container to align the control within.
     */
    virtual void align(Control* control, const Container* container);

    /**
     * Touch callback on touch events.  Coordinates are given relative to the container's
     * content area.
     *
     * @param evt The touch event that occurred.
     * @param x The x position of the touch in pixels. Left edge is zero.
     * @param y The y position of the touch in pixels. Top edge is zero.
     * @param contactIndex The order of occurrence for multiple touch contacts starting at zero.
     *
     * @see Touch::TouchEvent
     */
    virtual bool touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);
};

}

#endif