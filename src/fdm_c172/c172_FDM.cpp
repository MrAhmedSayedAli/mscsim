/***************************************************************************//**
 *
 * @author Marek M. Cel <marekcel@marekcel.pl>
 *
 * @section LICENSE
 *
 * Copyright (C) 2020 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#include <fdm_c172/c172_FDM.h>

////////////////////////////////////////////////////////////////////////////////

using namespace fdm;

////////////////////////////////////////////////////////////////////////////////

C172_FDM::C172_FDM( const DataInp *dataInpPtr, DataOut *dataOutPtr, bool verbose ) :
    FDM( dataInpPtr, dataOutPtr, verbose )
{
    FDM::_aircraft = _aircraft = new C172_Aircraft( _rootNode );
}

////////////////////////////////////////////////////////////////////////////////

C172_FDM::~C172_FDM()
{
    FDM_DELPTR( _aircraft );
}

////////////////////////////////////////////////////////////////////////////////

void C172_FDM::updateDataOut()
{
    /////////////////////
    FDM::updateDataOut();
    /////////////////////

    // controls
    _dataOut.controls.ailerons = _aircraft->getCtrl()->getAilerons();
    _dataOut.controls.elevator = _aircraft->getCtrl()->getElevator();
    _dataOut.controls.rudder   = _aircraft->getCtrl()->getRudder();
    _dataOut.controls.flaps    = _aircraft->getCtrl()->getFlaps();

    // propulsion
    _dataOut.engine[ 0 ].state = _aircraft->getProp()->getEngine()->getState() == C172_Engine::Running;
    _dataOut.engine[ 0 ].rpm = _aircraft->getProp()->getEngine()->getRPM();
    _dataOut.engine[ 0 ].map = _aircraft->getProp()->getEngine()->getMAP();
    _dataOut.engine[ 0 ].fuelFlow = _aircraft->getProp()->getEngine()->getFuelFlow();
}
