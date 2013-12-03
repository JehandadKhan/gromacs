/*
 * This file is part of the GROMACS molecular simulation package.
 *
 * Copyright (c) 2013, by the GROMACS development team, led by
 * David van der Spoel, Berk Hess, Erik Lindahl, and including many
 * others, as listed in the AUTHORS file in the top-level source
 * directory and at http://www.gromacs.org.
 *
 * GROMACS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * GROMACS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GROMACS; if not, see
 * http://www.gnu.org/licenses, or write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 *
 * If you want to redistribute modifications to GROMACS, please
 * consider that scientific software is very special. Version
 * control is crucial - bugs must be traceable. We will be happy to
 * consider code for inclusion in the official distribution, but
 * derived work must not be called official GROMACS. Details are found
 * in the README & COPYING files - if they are missing, get the
 * official version at http://www.gromacs.org.
 *
 * To help us fund GROMACS development, we humbly ask that you cite
 * the research papers on the package. Check out http://www.gromacs.org.
 */
/*! \libinternal \file
 * \brief
 * Declares code for calling GROMACS routines from an external program
 *
 * \author David van der Spoel <david.vanderspoel@icm.uu.se>
 * \ingroup module_qmmm
 */
#ifndef GMX_MMSLAVE_MMSLAVE_H
#define GMX_MMSLAVE_MMSLAVE_H

#include <vector>

namespace gmx
{

/*! \brief
 * class for serving a quantum chemistry program by computing energies and forces
 */
class MMSlave
{
    private:
        //! Simulation parameters
        t_inputrec       inputrec_;
        //! Simulation box
        matrix           box_;
        //! Molecular topology
        gmx_mtop_t       mtop_;
        //! Coordinates
        rvec            *x_;
        //! Velocities
        rvec            *v_;
        //! Forces
        rvec            *f_;
        //! Group size
        std::vector<int> groupSize_;       
    public:
        //! Constructor
        MMSlave();

        //! Destructor
        ~MMSlave() {}

        /*! \brief
         * Function to read a tpr file and store the information in the
         * data structur
         * \param[in] tpr  the file name
         * \return true if successful
         */
        bool readTpr(const char *tpr);

        /*! \brief
         * Copy internal coordinate array
         * \param[in]  natoms length of array
         * \param[out] x      array of rvecs (must be allocated by the caller)
         * \return true on success, false otherwise (typically if natoms is too small or x is NULL)
         */
        bool copyX(int natoms, rvec *x);

        /*! \brief
         * Copy internal velocity array
         * \param[in]  natoms length of array
         * \param[out] v      array of rvecs (must be allocated by the caller)
         * \return true on success, false otherwise (typically if natoms is too small or v is NULL)
         */
        bool copyV(int natoms, rvec *v);

        /*! \brief
         * Copy internal force array
         * \param[in]  natoms length of array
         * \param[out] f      array of rvecs (must be allocated by the caller)
         * \return true on success, false otherwise (typically if natoms is too small or f is NULL)
         */
        bool copyF(int natoms, rvec *f);

        /*! \brief
         * Clean up function
         */
        void cleanUp();

        /*! \brief
         * Function to modify the charge of an atom
         * data structure
         * \param[in] id   the atom id
         * \param[in] q    the new charge
         * \return true if successful
         */
        bool setAtomQ(atom_id id, double q);

        /*! \brief
         * Function to receive the charge of an atom
         * data structure
         * \param[in] id   the atom id
         * \param[out] q   the charge
         * \return true if successful
         */
        bool getAtomQ(atom_id id, double *q);

        /*! \brief
         * Function to receive the charge of an atom
         * data structure
         * \param[in] id   the atom id
         * \param[out] n   the atom number
         * \return true if successful
         */
        bool getAtomNumber(atom_id id, int *n);
        
        /*! \brief
         * Function to compute the energy and forces
         * \param[in]  x   the atomic coordinates for the whole system (MM+QM)
         * \param[out] f   the forces on all atoms
         * \param[out] energy the total MM energy
         * \return TRUE if successful
         */
        bool calcEnergy(const rvec *x,
                        rvec       *f,
                        double     *energy);
};

}

#endif