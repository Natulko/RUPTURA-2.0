#include <exception>
#include <chrono>

#include "special_functions.h"

#include "inputreader.h"
#include "breakthrough.h"
#include "mixture_prediction.h"
#include "fitting.h"


int main(void)
{
  try 
  {
    InputReader reader("simulation.input");

    switch(reader.simulationType)
    {
      case InputReader::SimulationType::Breakthrough:
      default:
      {

				Breakthrough breakthrough(reader);

				std::cout << breakthrough.repr();
				breakthrough.initialize();
				breakthrough.createPlotScript();
				breakthrough.createMovieScripts();

				// Measure the time the simulation takes to run
				const auto before = std::chrono::high_resolution_clock::now();

				// run the simulation with the implicit solver
				breakthrough.run( true );

				const auto diff = std::chrono::high_resolution_clock::now() - before;
				const auto millis = (int)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

				std::cout << "it took " << (double) millis / 1000 << "seconds." << std::endl;


        break;
      }
      case InputReader::SimulationType::MixturePrediction:
      {
        MixturePrediction mixture(reader);

        std::cout << mixture.repr();
        mixture.run();
        mixture.createPureComponentsPlotScript();
        mixture.createMixturePlotScript();
        mixture.createMixtureAdsorbedMolFractionPlotScript();
        mixture.createPlotScript();
        std::cout << mixture.repr();
        break;
      }
      case InputReader::SimulationType::Fitting:
      {
        Fitting fitting(reader);

        fitting.run();
        break;
      }
    }
  }
  catch (std::exception const& e)
  {
    std::cerr << e.what();
    exit(-1);
  }

  return 0;
}
