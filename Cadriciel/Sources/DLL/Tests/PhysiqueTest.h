//////////////////////////////////////////////////////////////////////////////
/// @file PhysiqueTest.h
/// @author Olivier St-Amour 
/// @date 2016-02-29
/// @version 2.2
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef PHYSIQUE_TEST_H
#define PHYSIQUE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "Utilitaire.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstraitTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe NoeudAbstrait
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class PhysiqueTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
  CPPUNIT_TEST_SUITE( PhysiqueTest );
  CPPUNIT_TEST( testIntersectionQuad );
  CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// D�finissez ici les diff�rents cas de tests...
	// =================================================================

	/// Cas de test: verification de l'intersection de deux quads.
	void testIntersectionQuad();

private:
    utilitaire::QuadEnglobant quad1_;
    utilitaire::QuadEnglobant quad2_;
};

#endif // PHYSIQUE_TEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

