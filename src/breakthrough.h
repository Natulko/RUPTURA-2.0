#include <cstddef>
#include <vector>
#include <tuple>
#include <ctime>

#include "component.h"
#include "inputreader.h"
#include "mixture_prediction.h"

#include <cvode/cvode.h> /* main integrator header file                 */
#include <math.h>
#include <nvector/nvector_serial.h> /* serial N_Vector types, fct. and macros      */
#include <stdio.h>
#include <stdlib.h>
#include <sundials/sundials_dense.h> /* use generic DENSE solver in preconditioning */
#include <sundials/sundials_logger.h>
#include <sundials/sundials_types.h> /* definition of sunrealtype                      */
#include <sunlinsol/sunlinsol_spbcgs.h> /* access to SPBCGS SUNLinearSolver            */
#include <sunlinsol/sunlinsol_spfgmr.h> /* access to SPFGMR SUNLinearSolver            */
#include <sunlinsol/sunlinsol_spgmr.h> /* access to SPGMR SUNLinearSolver             */
#include <sunlinsol/sunlinsol_sptfqmr.h> /* access to SPTFQMR SUNLinearSolver           */
#include <sunnonlinsol/sunnonlinsol_newton.h> /* access to Newton SUNNonlinearSolver         */
#include <sunmatrix/sunmatrix_dense.h>
#include <sunlinsol/sunlinsol_dense.h>

#ifdef PYBUILD
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
namespace py = pybind11;
#endif  // PYBUILD


struct Breakthrough
{

		void computeFirstDerivatives(std::vector<double> &dqdt,
																 std::vector<double> &dpdt,
																 const std::vector<double> &q_eq,
																 const std::vector<double> &q,
																 const std::vector<double> &v,
																 const std::vector<double> &p);

		void computeEquilibriumLoadings();

		void computeVelocity();

public:
    Breakthrough(const InputReader &inputreader);
    Breakthrough(std::string _displayName, std::vector<Component> _components, size_t _carrierGasComponent,
                 size_t _numberOfGridPoints, size_t _printEvery, size_t _writeEvery, double _temperature,
                 double _p_total, double _columnVoidFraction, double _pressureGradient, double _particleDensity,
                 double _columnEntranceVelocity, double _columnLength, double _timeStep, size_t _numberOfTimeSteps,
                 bool _autoSteps, bool _pulse, double _pulseTime, const MixturePrediction _mixture);

    std::string repr() const;
    void initialize();
    void run( bool impl );
    void computeStep(size_t step);

    void createPlotScript();
    void createMovieScripts();

#ifdef PYBUILD
    py::array_t<double> compute();
#endif  // PYBUILD

   private:

    const std::string displayName;
    const std::vector<Component> components;
    size_t carrierGasComponent{ 0 };
		size_t Ncomp;      // number of components
		size_t Ngrid;      // number of grid points

    size_t printEvery; // print time step to the screen every printEvery steps
    size_t writeEvery; // write data to files every writeEvery steps

		bool implicit;

    double T;          // absolute temperature [K]
    double p_total;    // total pressure column [Pa]
    double dptdx;      // pressure gradient [N/m3]
    double epsilon;    // void-fraction of the column [-]
    double rho_p;      // particle density [kg/m3]
    double v_in;       // interstitial velocity at the begin of the column [m/s]
    
    double L;          // length of the column
    double dx;         // spacing in spatial direction
    double dt;         // timestep integration
    size_t Nsteps;     // total number of steps
    bool autoSteps;    // use automatic number of steps
    bool pulse;        // pulsed inlet condition for breakthrough
    double tpulse;     // pulse time
    MixturePrediction mixture;
    size_t maxIsothermTerms;
    std::pair<size_t, size_t> iastPerformance{ 0, 0 };
    
    // vector of size 'Ncomp'
    std::vector<double> prefactor;
    std::vector<double> Yi;        // ideal gas mol-fraction for each component
    std::vector<double> Xi;        // adsorbed mol-fraction for each component
    std::vector<double> Ni;        // number of molecules for each component

    // vector of size '(Ngrid + 1)'
    std::vector<double> V;         // interstitial gas velocity along the column
		std::vector<double> Pt;        // total pressure along the column


//    std::vector<double> P;         // partial pressure at every grid point for each component
//		std::vector<double> Q;         // volume-averaged adsorption amount at every grid point for each component

		// derivative of P with respect to time
    std::vector<double> Dpdtnew;
		// derivative of Q with respect to time
    std::vector<double> Dqdtnew;
    std::vector<double> cachedP0;  // cached hypothetical pressure
    std::vector<double> cachedPsi; // cached reduced grand potential over the column

		// objects for sundials setup
		SUNContext sunContext;
		SUNLogger sunLogger;
		N_Vector u;										// Solver's solution vector storing both Q and P
		SUNMatrix A;									// Solver's matrix object for the Jacobian matrix
		void *cvodeMem;
		SUNNonlinearSolver solver;
		SUNLinearSolver linSolver;




		enum class IntegrationScheme
    {
      SSP_RK = 0,
      Iterative = 1
    };

		//static int f(sunrealtype t, N_Vector u, N_Vector udot, void* user_data);

		void createMovieScriptColumnV();
    void createMovieScriptColumnPt();
    void createMovieScriptColumnQ();
    void createMovieScriptColumnQeq();
    void createMovieScriptColumnP();
    void createMovieScriptColumnDpdt();
    void createMovieScriptColumnDqdt();
    void createMovieScriptColumnPnormalized();

public:
		size_t numCalls {0};

		// vector of size '(Ngrid + 1)'
		std::vector<double> Vnew;					// storage for velocity during solving

		// vector of size '(Ngrid + 1) * Ncomp', for each grid point, data per component (contiguous)
		std::vector<double> P;						// partial pressure at every grid point for each component
		std::vector<double> Pnew;
		std::vector<double> Q;						// volume-averaged adsorption amount at every grid point for each component
		std::vector<double> Qnew;
		std::vector<double> Dqdt;					// derivative of Q over time
		std::vector<double> Dpdt;					// derivative of P over time

		// equilibrium adsorption amount at every grid point for each component
		std::vector<double> Qeq;
		std::vector<double> Qeqnew;
};
