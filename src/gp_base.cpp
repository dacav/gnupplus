#include <gnup.hpp>
#include <cstdio>
#include <cstring>

namespace gnup {

    Plot::Plot (unsigned xs)
    {
        axis = xs;
        trigger = NULL;
    }

    Plot::~Plot ()
    {
        DataSet::iterator i, end;

        end = data.end();
        for (i = data.begin(); i != end; i ++) {
            delete[] *i;
        }
    }

    void Plot::addVector (float *vals, size_t n)
    {
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

    void Plot::getIters (DataSet::iterator &b, DataSet::iterator &e)
    {
        b = data.begin();
        e = data.end();
    }

    unsigned Plot::getAxis ()
    {
        return axis;
    }

    GnuPlot::GnuPlot (const char *prog) throw (CommError)
           : Comm(prog)
    {
        enab_axis = Plot::AXIS_NONE;
    }

    void GnuPlot::addSource (Plot &src)
    {
        sources.push_back(&src);
        src.setTrigger(this);
        enab_axis |= src.getAxis();
    }

    unsigned GnuPlot::countEnabAxis ()
    {
        register unsigned enab = enab_axis;
        unsigned count = 0;

        if (enab & Plot::AXIS_X) {
            count ++;
        }
        if (enab & Plot::AXIS_Y) {
            count ++;
        }
        if (enab & Plot::AXIS_Z) {
            count ++;
        }
        return count;
    }

    void GnuPlot::trig ()
    {
        size_t size;
        std::list<Plot *>::iterator i, end;

        size = sources.size();
        if (size == 0) {
            // Nothing to plot...
            return;
        }
        
        // Format initialization phase: gnuplot must know in advance which
        // plots must be achieved.
        switch (countEnabAxis()) {
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
        // We know that this operation will be achieved at least once,
        // since size > 0
        do {
            Plot *src = *i;
            src->giveFormat(this);
            i ++;
            if (--size) {
                // This puts the comma between two plotting indications.
                command(", ");
            }
        } while (i != end);
        command("\n");

        // Actual plotting phase
        for (i = sources.begin(); i != sources.end(); i ++) {
            Plot *src = *i;
            src->givePlotting(this);
            // Terminate data set
            command("e\n");
        }
    }

}

