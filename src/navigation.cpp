#include "navigation.impl.hpp"

#include "url.impl.hpp"

extern "C"
{
    void saucer_navigation_free(saucer_navigation *navigation)
    {
        delete navigation;
    }

    saucer_navigation *saucer_navigation_move(saucer_navigation *navigation)
    {
        return saucer_navigation::from(std::move(**navigation));
    }

    saucer_url *saucer_navigation_url(saucer_navigation *navigation)
    {
        return saucer_url::from((**navigation)->url());
    }

    bool saucer_navigation_new_window(saucer_navigation *navigation)
    {
        return (**navigation)->new_window();
    }

    bool saucer_navigation_redirection(saucer_navigation *navigation)
    {
        return (**navigation)->redirection();
    }

    bool saucer_navigation_user_initiated(saucer_navigation *navigation)
    {
        return (**navigation)->user_initiated();
    }
}
