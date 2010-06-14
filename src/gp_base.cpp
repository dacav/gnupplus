#include <gnup.hpp>
#include <cstdio>
#include <cstring>

namespace gnup {

    Plot::Plot (const char *tit)
    {
        trigger = NULL;
        title = tit;
        flags = 0;
    }

    Plot::~Plot ()
    {
        DataSet::iterator i, end;

        end = data.end();
        for (i = data.begin(); i != end; i ++) {
            delete[] *i;
        }
    }

    void Plot::addVector (float *vals)
    {
        size_t n = getDimension();
        float *v = new float[n];
        memcpy((void *)v, (void *)vals, n * sizeof(float));

        data.push_back(v);
        if (trigger) {
            trigger->trig();
        }
    }

    void Plot::setTrigger (Trigger *t)
    {
        trigger = t;
    }

    void Plot::getPlotting (Comm *c)
    {
        getPlotting(c, data.begin(), data.end());
    }

    const char * Plot::getTitle ()
    {
        return title;
    }

    static const unsigned PL_WITH_LINES = 1 << 0;

    void Plot::setWithLines (bool wl)
    {
        if (wl) flags |= PL_WITH_LINES;
        else flags &= ~PL_WITH_LINES;
    }

    bool Plot::getWithLines ()
    {
        return (bool) (flags & PL_WITH_LINES);
    }

    GnuPlot::GnuPlot (size_t dims, const char *prog) throw (CommError)
           : Comm(prog)
    {
        dimensions = dims;
    }

    void GnuPlot::addSource (Plot &src) throw (PlotError)
    {
        if (src.getDimension() > dimensions) {
            PlotError err("Too many dimensions");
            throw err;
        } else {
            sources.push_back(&src);
            src.setTrigger(this);
        }
    }

    void GnuPlot::initPlotting ()
    {
        size_t size;
        std::list<Plot *>::iterator i, end;

        // Format initialization phase: gnuplot must know in advance which
        // plots must be achieved.
        switch (dimensions) {
            case 0:
                // Nothing to plot (it should never be the case)
                return;
            case 1:
            case 2:
                command("plot ");
                break;
            default:
                command("splot ");
        }

        i = sources.begin();
        end = sources.end();
        size = sources.size();
        // We know that this operation will be achieved at least once,
        // since size > 0
        do {
            Plot *src = *i;
            const char *title = src->getTitle();

            command("\"-\" ");
            if (title != NULL) command("title \"%s\" ", title);
            else command("notitle");

            // Plot specific data settings:
            src->getFormat(this);
            if (src->getWithLines()) {
                command("w l ");
            }

            if (--size) {
                // This puts the comma between two plotting indications.
                command(", ");
            }
        } while ((++ i) != end);
        command("\n");
    }

    void GnuPlot::trig ()
    {
        std::list<Plot *>::iterator i, end;

        if (sources.size() == 0) {
            // Nothing to plot...
            return;
        }

        initPlotting();
        
        // Actual plotting phase
        for (i = sources.begin(); i != sources.end(); i ++) {
            Plot *src = *i;
            src->getPlotting(this);
            // Terminate data set
            command("e\n");
        }
    }

}

