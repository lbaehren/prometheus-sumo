/***************************************************************************
 *   Copyright (C) 2012                                                    *
 *   Lars B"ahren (lbaehren@gmail.com)                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef CONFIG_RUBY_GEMS_H
#define CONFIG_RUBY_GEMS_H

#include "ConfigFileBase.h"

// ==============================================================================
//
//  Class definition
//
// ==============================================================================

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    /*!
      \file RubyGems.h
      \class RubyGems
      \ingroup prometheus
      \ingroup config
      \brief Configuration settings for required Ruby gems
      \test testConfigRubyGems.cc

      \author Lars Baehren
      \date 2012-10-22

      This class provides an adapter to read configuration data on list of 
      required Ruby gems, most of which are used for the \ref pandora web
      application and \ref homepage.
    */
    class RubyGems : public ConfigFileBase {

    protected:

      //! Parameters for the 'gem' node of the configuration file
      struct GemParameters {
	//! Name of the gem
	std::string name;
	//! URL for gem's project page
	std::string url;
	//! Description of the gem
	std::string description;
	//! Version specification
	std::string version;
      };

    private:

      //! List of gems for which parameters are kept
      std::vector<GemParameters> itsGemList;

      //! Store the data from an individual node
      bool storeNode (YAML::Iterator const &it);

    public:

      // === Construction =======================================================

      //! Default constructor
      RubyGems ();

      //! Argumented constructor
      RubyGems (std::string const &filename);

      // === Parameter access ===================================================

      //! Get the number of gems for which parameters are kept
      inline size_t nofGems () {
	return itsGemList.size();
      }
      
      //! Get the name of the gems
      std::set<std::string> names ();

      // === Public functions ===================================================

      //! Provide a summary of the object's internal parameters and status
      inline void summary () {
	summary (std::cout);
      }
      
      //! Provide a summary of the object's internal parameters and status
      void summary (std::ostream &os);

    };

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END

#endif
