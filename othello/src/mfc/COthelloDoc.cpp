/*
On ne dit pas... javellis�, mais... j'ai lu.
On ne dit pas... un enfoir�, mais... une ann�e de perdue.
On ne dit pas... il a particip�, mais... il est parti pisser.
On ne dit pas... une biroute, mais... une route � deux voies.
On ne dit pas... d�g�ts des eaux, mais... des marins.
On ne dit pas... je suis paniqu�e, mais... je cherche un mec.
On ne dit pas... ad�quation, mais... y a-t-il des questions.
On ne dit pas... je suppute, mais... je suis p�ripat�ticienne.
On ne dit pas... je suis tr�s sain, mais... j'aime les gros nichons.
On ne dit pas... un conquistador, mais... un imb�cile narcissique.
On ne dit pas... j'ai vaincu, mais... je suis pluri-anal.
On ne dit pas... faire des vendanges, mais... p�ter comme un dieu.
On ne dit pas... un microprocesseur, mais... un petit prof.
On ne dit pas... jerrican, mais... je m'bidonne.
On ne dit pas... un eunologue, mais... un sexologue.
On ne dit pas... un homme hors paire, mais... un eunuque.
On ne dit pas... couper le beurre, mais... circoncire.
On ne dit pas... il s'est �lev� � la force du poignet, mais... un branleur.
On ne dit pas... barbecue, mais... poils aux fesses.
On ne dit pas... une bonne paella, mais... la bonne espagnole est absente.
On ne dit pas... m�lodie en sous-sol, mais... gare notre voiture au parking.
On ne dit pas... je tripote, mais... j'ai trois amis.
On ne dit pas... le processus de paix est enclench�, mais... je vais l�cher une caisse.
On ne dit pas... �triqu�, mais... j'ai band�.
On ne dit pas... une dame pipi,... mais... un chef de cabinet.
On ne dit pas... je mastique,... mais... je m'en branle.
On ne dit pas... c'est alligator, mais... c'est Mouloud qui a raison.
On ne dit pas... allopathie, mais... vous �tes en communication avec un.
On ne dit pas... un pinailleur, mais... ... un mari infid�le.
On ne dit pas... Loto sportif, mais... une voiture GTI.
On ne dit pas... all�gro, mais... vas y boudin.
On ne dit pas... j'alphab�tise, mais... ... j'ai fait une connerie.
*/
// COthelloDoc.cpp : implementation of the COthelloDoc class
//

#include "stdafx.h"
#include "Othello.h"

#include "COthelloDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COthelloDoc

IMPLEMENT_DYNCREATE(COthelloDoc, CDocument)

BEGIN_MESSAGE_MAP(COthelloDoc, CDocument)
END_MESSAGE_MAP()


// COthelloDoc construction/destruction

COthelloDoc::COthelloDoc()
{
	// TODO: add one-time construction code here

}

COthelloDoc::~COthelloDoc()
{
}

BOOL COthelloDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// COthelloDoc serialization

void COthelloDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// COthelloDoc diagnostics

#ifdef _DEBUG
void COthelloDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COthelloDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COthelloDoc commands
