//-----------------------------------------------------------------------------
// File:     OpenSimQtStartSimulation.h
// Class:    OpenSimQtStartSimulation.h
// Parent:   QObject
// Purpose:  Class that starts simulation.
/* ------------------------------------------------------------------------- *
*                                 OpenSimQt                                  *
* -------------------------------------------------------------------------- *
* OpenSimQt was developed with support from Simbios (the NIH National Center *
* for Physics-Based Simulation Biological Structures at Stanford) under NIH  *
* Roadmap for Medical Research grant U54 GM072970 and from NCSRR (National   *
* Center for Simulation in Rehabilitation Research) under NIH research       *
* infrastructure grant R24 HD065690.                                         *
*                                                                            *
* Portions copyright (c) 2011 the Authors and Stanford University.           *
* Authors: Paul Mitiguy                                                      *
* Contributors: Ayman Habib, Michael Sherman                                 *
*                                                                            *
* Permission is hereby granted, free of charge, to any person obtaining a    *
* copy of this software and associated documentation files (the "Software"), *
* to deal in the Software without restriction, including without limitation  *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
* and/or sell copies of the Software, and to permit persons to whom the      *
* Software is furnished to do so, subject to the following conditions:       *
*                                                                            *
* This sentence, the above copyright and permission notices, and the         *
* following disclaimer shall be included in all copies or substantial        *
* portions of the Software.                                                  *
*                                                                            *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
* THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
* USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
* -------------------------------------------------------------------------- */
#include "OpenSimQtStandardHeaders.h"
#if 0                             // Change 1 to 0 if want to use Simbody only.
   #include <SimTKsimbody.h>      // Includes all Simbody header files.
   using namespace SimTK;
#else
   #include <OpenSim.h>           // Includes all OSimAPI header files.
   namespace OSimAPI = OpenSim;   // Avoid confusion between OpenSimQt and OpenSim namespaces
   using namespace OSimAPI;
   using namespace SimTK;
#endif

//------------------------------------------------------------------------------
namespace OpenSimQt {


//-----------------------------------------------------------------------------
// Prototypes for local functions (functions not called by code in other files)
//-----------------------------------------------------------------------------
bool  WriteExceptionToFile( const char* outputString, const char* exceptionStringOrNull )
{
   bool retValue = false;

#if OPENSIM_QT_DEBUG__
   FILE *outputFile = fopen( "C:\\OpenSimQt\\ExceptionsThrown.txt", "a+" );
   if( outputFile && outputString )
   {
      retValue = fputs( outputString, outputFile ) != EOF;
      if( exceptionStringOrNull ) retValue = retValue && fputs( exceptionStringOrNull, outputFile ) != EOF;
      fflush( outputFile );
      fclose( outputFile );
   }
#endif
   return retValue;
}


//-----------------------------------------------------------------------------
bool  StartAndRunSimulationMathematicsInsideExceptionHandling( )
{
#if 1
		// Create an OpenSim model and set its name
		Model osimModel;
		osimModel.setName( "tugOfWar" );

		// GROUND BODY
		// Get a reference to the model's ground body
		OpenSim::Body& ground = osimModel.getGroundBody();

		// Add display geometry to the ground to visualize in the GUI
		FILE *Fptr = fopen( "\\OpenSim2.2.1\\sdk\\APIExamples\\ExampleMain\\ground.vtp", "r" );

		ground.addDisplayGeometry( "\\OpenSim2.2.1\\sdk\\APIExamples\\ExampleMain\\ground.vtp" );
		ground.addDisplayGeometry( "\\OpenSim2.2.1\\sdk\\APIExamples\\ExampleMain\\anchor1.vtp" );
		ground.addDisplayGeometry( "\\OpenSim2.2.1\\sdk\\APIExamples\\ExampleMain\\anchor2.vtp" );

		// BLOCK BODY

		// Specify properties of a 20 kg, 0.1 m^3 block body
		double blockMass = 20.0, blockSideLength = 0.1;
		Vec3 blockMassCenter(0);
		Inertia blockInertia = blockMass*Inertia::brick(blockSideLength, blockSideLength, blockSideLength);

		// Create a new block body with the specified properties
		OpenSim::Body *block = new OpenSim::Body("block", blockMass, blockMassCenter, blockInertia);

		// Add display geometry to the block to visualize in the GUI
		block->addDisplayGeometry("block.vtp");

		// FREE JOINT

		// Create a new free joint with 6 degrees-of-freedom (coordinates) between the block and ground bodies
		Vec3 locationInParent(0, blockSideLength/2, 0), orientationInParent(0), locationInBody(0), orientationInBody(0);
		FreeJoint *blockToGround = new FreeJoint("blockToGround", ground, locationInParent, orientationInParent, *block, locationInBody, orientationInBody);

		// Get a reference to the coordinate set (6 degrees-of-freedom) between the block and ground bodies
		CoordinateSet& jointCoordinateSet = blockToGround->getCoordinateSet();

		// Set the angle and position ranges for the coordinate set
		double angleRange[2] = {-SimTK::Pi/2, SimTK::Pi/2};
		double positionRange[2] = {-1, 1};
		jointCoordinateSet[0].setRange(angleRange);
		jointCoordinateSet[1].setRange(angleRange);
		jointCoordinateSet[2].setRange(angleRange);
		jointCoordinateSet[3].setRange(positionRange);
		jointCoordinateSet[4].setRange(positionRange);
		jointCoordinateSet[5].setRange(positionRange);

		// Add the block body to the model
		osimModel.addBody(block);

		///////////////////////////////////////////////
		// DEFINE THE SIMULATION START AND END TIMES //
		///////////////////////////////////////////////

		// Define the initial and final simulation times
		double initialTime = 0.0;
		double finalTime = 4.0;

		/////////////////////////////////////////////
		// DEFINE CONSTRAINTS IMPOSED ON THE MODEL //
		/////////////////////////////////////////////

		// Specify properties of a point on a line constraint to limit the block's motion
		Vec3 lineDirection(1,0,-1);
		Vec3 pointOnLine(1,0,-1);
		Vec3 pointOnFollowerBody(0,-0.05,0);

		// Create a new point on a line constraint
		PointOnLineConstraint *lineConstraint = new PointOnLineConstraint(ground, lineDirection, pointOnLine, *block, pointOnFollowerBody);

		// Add the new point on a line constraint to the model
		osimModel.addConstraint(lineConstraint);

		///////////////////////////////////////
		// DEFINE FORCES ACTING ON THE MODEL //
		///////////////////////////////////////
		// GRAVITY

		// Define the acceleration due to gravity
		osimModel.setGravity(Vec3(0,-9.80665,0));

		// MUSCLE FORCES

		// Create two new muscles
		double maxIsometricForce = 1000.0, optimalFiberLength = 0.1, tendonSlackLength = 0.2, pennationAngle = 0.0, activation = 0.0001, deactivation = 1.0;
		// Create new muscle 1 using the Shutte 1993 muscle model
		// Note: activation/deactivation parameters are set differently between the models.
		Thelen2003Muscle *muscle1 = new Thelen2003Muscle("muscle1",maxIsometricForce,optimalFiberLength,tendonSlackLength,pennationAngle);
		muscle1->setActivationTimeConstant(activation);
		muscle1->setDeactivationTimeConstant(deactivation);
		// Create new muscle 2 using the Thelen 2003 muscle model
		Thelen2003Muscle *muscle2 = new Thelen2003Muscle("muscle2",maxIsometricForce,optimalFiberLength,tendonSlackLength,pennationAngle);
		muscle2->setActivationTimeConstant(activation);
		muscle2->setDeactivationTimeConstant(deactivation);

		// Specify the paths for the two muscles
		// Path for muscle 1
		muscle1->addNewPathPoint("muscle1-point1", ground, Vec3(0.0,0.05,-0.35));
		muscle1->addNewPathPoint("muscle1-point2", *block, Vec3(0.0,0.0,-0.05));
		// Path for muscle 2
		muscle2->addNewPathPoint("muscle2-point1", ground, Vec3(0.0,0.05,0.35));
		muscle2->addNewPathPoint("muscle2-point2", *block, Vec3(0.0,0.0,0.05));

		// Add the two muscles (as forces) to the model
		osimModel.addForce(muscle1);
		osimModel.addForce(muscle2);

		// CONTACT FORCE

		// Define contact geometry
		// Create new floor contact halfspace
		ContactHalfSpace *floor = new ContactHalfSpace(SimTK::Vec3(0), SimTK::Vec3(0, 0, -0.5*SimTK_PI), ground, "floor");
		// Create new cube contact mesh
		OpenSim::ContactMesh *cube = new OpenSim::ContactMesh("\\OpenSim2.2.1\\sdk\\APIExamples\\ExampleMain\\blockRemesh192.obj", SimTK::Vec3(0), SimTK::Vec3(0), *block, "cube");

		// Add contact geometry to the model
		osimModel.addContactGeometry(floor);
		osimModel.addContactGeometry(cube);

		// Contact parameters
		double stiffness = 1.0e8, dissipation = 0.01, friction = 0.25;

		// Define contact parameters for elastic foundation force
		OpenSim::ElasticFoundationForce::ContactParameters *contactParams = new OpenSim::ElasticFoundationForce::ContactParameters(stiffness, dissipation, friction, 0, 0);
		contactParams->addGeometry("cube");
		contactParams->addGeometry("floor");

		// Create a new elastic foundation (contact) force between the floor and cube.
		OpenSim::ElasticFoundationForce *contactForce = new OpenSim::ElasticFoundationForce(contactParams);
		contactForce->setName("contactForce");

		// Add the new elastic foundation force to the model
		osimModel.addForce(contactForce);

		// PRESCRIBED FORCE

		// Specify properties of a force function to be applied to the block
		double time[2] = {0, finalTime};					// time nodes for linear function
		double fXofT[2] = {0,  -blockMass*9.80665*3.0};		// force values at t1 and t2
		double pXofT[2] = {0, 0.1};							// point in x values at t1 and t2

		// Create a new linear functions for the force and point components
		PiecewiseLinearFunction *forceX = new PiecewiseLinearFunction(2, time, fXofT);
		PiecewiseLinearFunction *pointX = new PiecewiseLinearFunction(2, time, pXofT);

		// Create a new prescribed force applied to the block
		PrescribedForce *prescribedForce = new PrescribedForce(block);
		prescribedForce->setName("prescribedForce");

		// Set the force and point functions for the new prescribed force
		prescribedForce->setForceFunctions(forceX, new Constant(0.0), new Constant(0.0));
		prescribedForce->setPointFunctions(pointX, new Constant(0.0), new Constant(0.0));

		// Add the new prescribed force to the model
		osimModel.addForce(prescribedForce);

		///////////////////////////////////
		// DEFINE CONTROLS FOR THE MODEL //
		///////////////////////////////////
		// Create a prescribed controller that simply applies controls as function of time
		PrescribedController *muscleController = new PrescribedController();
		muscleController->setActuators(osimModel.updActuators());
		// Define linear functions for the control values for the two muscles
		Array<double> slopeAndIntercept1(0.0, 2);  // array of 2 doubles
		Array<double> slopeAndIntercept2(0.0, 2);
		// muscle1 control has slope of -1 starting 1 at t = 0
		slopeAndIntercept1[0] = -1.0/(finalTime-initialTime);  slopeAndIntercept1[1] = 1.0;
		// muscle2 control has slope of 1 starting 0.05 at t = 0
		slopeAndIntercept2[0] = 1.0/(finalTime-initialTime);  slopeAndIntercept2[1] = 0.05;

		// Set the indiviudal muscle control functions for the prescribed muscle controller
		muscleController->prescribeControlForActuator("muscle1", new LinearFunction(slopeAndIntercept1));
		muscleController->prescribeControlForActuator("muscle2", new LinearFunction(slopeAndIntercept2));


		// Define the default states for the two muscles
		// Activation
		muscle1->setDefaultActivation(slopeAndIntercept1[1]);
		muscle2->setDefaultActivation(slopeAndIntercept2[1]);
		// Fiber length
		muscle2->setDefaultFiberLength(0.1);
		muscle1->setDefaultFiberLength(0.1);

		//////////////////////////
		// PERFORM A SIMULATION //
		//////////////////////////

		// Initialize the system and get the default state
		SimTK::State &si = osimModel.initSystem();

		// Define non-zero (defaults are 0) states for the free joint
		CoordinateSet& modelCoordinateSet = osimModel.updCoordinateSet();
		modelCoordinateSet[3].setValue(si, blockSideLength); // set x-translation value
		modelCoordinateSet[3].setSpeedValue(si, 0.1); // set x-speed value
		modelCoordinateSet[4].setValue(si, blockSideLength/2+0.01); // set y-translation value

		// Compute initial conditions for muscles
		osimModel.computeEquilibriumForAuxiliaryStates(si);

		// Create the integrator, force reporter, and manager for the simulation.
		// Create the integrator
		SimTK::RungeKuttaMersonIntegrator integrator( osimModel.getMultibodySystem() );
		integrator.setAccuracy(1.0e-4);

		// Create the force reporter
		ForceReporter* reporter = new ForceReporter(&osimModel);
		osimModel.addAnalysis(reporter);

		// Create the manager
		Manager manager(osimModel,  integrator);

		// Print out details of the model
		osimModel.printDetailedInfo(si, std::cout);

		// Print out the initial position and velocity states
		si.getQ().dump("Initial q's"); // block positions
		si.getU().dump("Initial u's"); // block velocities
		std::cout << "Initial time: " << si.getTime() << std::endl;

		// Integrate from initial time to final time
		manager.setInitialTime(initialTime);
		manager.setFinalTime(finalTime);
		std::cout << "\n\nIntegrating from " << initialTime << " to " << finalTime << std::endl;
		manager.integrate(si);

		//////////////////////////////
		// SAVE THE RESULTS TO FILE //
		//////////////////////////////

		// Save the simulation results
		// Save the states
		Storage statesDegrees(manager.getStateStorage());
		statesDegrees.print("tugOfWar_states.sto");
		osimModel.updSimbodyEngine().convertRadiansToDegrees(statesDegrees);
		statesDegrees.setWriteSIMMHeader(true);
		statesDegrees.print("tugOfWar_states_degrees.mot");
		// Save the forces
		reporter->getForceStorage().print("tugOfWar_forces.mot");

		// Save the model to a file
		osimModel.print("tugOfWar_model.osim");


#else
   // Create the system, with subsystems for the bodies and some forces.
   MultibodySystem system;
   SimbodyMatterSubsystem matter(system);
   GeneralForceSubsystem forces(system);

   // Add gravity as a force element.
   Force::UniformGravity gravity(forces, matter, Vec3(0, -9.8, 0));

   // Create the body and some artwork for it.
   Body::Rigid pendulumBody(MassProperties(1.0, Vec3(0), Inertia(1)));
   pendulumBody.addDecoration(Transform(), DecorativeSphere(0.1).setColor(Red));

   // Add an instance of the body to the multibody system by connecting
   // it to Ground via a pin mobilizer.
   MobilizedBody::Pin pendulum(matter.updGround(), Transform(Vec3(0)),
                               pendulumBody, Transform(Vec3(0, 1, 0)));

   // Visualize with default options; ask for a report every 1/30 of a second
   // to match the Visualizer's default 30 frames per second rate.
   // The Simbody visualizer must be able to execute the program VisualizerGUI.exe
   // One way for Simbody to find this program is to set the environment variable
   // SimTK_INSTALL_DIR  with a value  FullPathTo/Simbody/bin  folder.
   Visualizer viz(system);
   system.addEventReporter(new Visualizer::Reporter(viz, 1./30));

   // Initialize the system and state.

   system.realizeTopology();
   State state = system.getDefaultState();
   pendulum.setOneU(state, 0, 1.0); // initial velocity 1 rad/sec

   // Simulate it.

   RungeKuttaMersonIntegrator integ(system);
   TimeStepper ts(system, integ);
   ts.initialize(state);
   ts.stepTo(10.0);

#endif

	 // Simulation completed properly
   return true;
}


//-----------------------------------------------------------------------------
bool  StartAndRunSimulationMathematics( )
{

   // The try-catch code in this main routine catches exceptions thrown by functions in the
   // try block, e.g., catching an exception that occurs when a NULL pointer is de-referenced.
   try
   {
      return StartAndRunSimulationMathematicsInsideExceptionHandling( );
   }

   // This catch statement handles certain types of exceptions
   catch( const std::exception &e )
   {
      WriteExceptionToFile( "\n\n Error: Programming error exception thrown:\n ", e.what() );
      return false;
   }

   // The exception-declaration statement (...) handles any type of exception,
   // including C exceptions and system/application generated exceptions.
   // This includes exceptions such as memory protection and floating-point violations.
   // An ellipsis catch handler must be the last handler for its try block.
   catch( ... )
   {
      WriteExceptionToFile( "\n\n Error: Programming error.  Unhandled exception.", NULL );
      return false;
   }


	 // Simulation completed properly
   return true;
}


//------------------------------------------------------------------------------
}  // End of namespace OpenSimQt



