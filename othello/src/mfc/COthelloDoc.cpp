/*
On ne dit pas... javellisé, mais... j'ai lu.
On ne dit pas... un enfoiré, mais... une année de perdue.
On ne dit pas... il a participé, mais... il est parti pisser.
On ne dit pas... une biroute, mais... une route à deux voies.
On ne dit pas... dégâts des eaux, mais... des marins.
On ne dit pas... je suis paniquée, mais... je cherche un mec.
On ne dit pas... adéquation, mais... y a-t-il des questions.
On ne dit pas... je suppute, mais... je suis péripatéticienne.
On ne dit pas... je suis très sain, mais... j'aime les gros nichons.
On ne dit pas... un conquistador, mais... un imbécile narcissique.
On ne dit pas... j'ai vaincu, mais... je suis pluri-anal.
On ne dit pas... faire des vendanges, mais... péter comme un dieu.
On ne dit pas... un microprocesseur, mais... un petit prof.
On ne dit pas... jerrican, mais... je m'bidonne.
On ne dit pas... un eunologue, mais... un sexologue.
On ne dit pas... un homme hors paire, mais... un eunuque.
On ne dit pas... couper le beurre, mais... circoncire.
On ne dit pas... il s'est élevé à la force du poignet, mais... un branleur.
On ne dit pas... barbecue, mais... poils aux fesses.
On ne dit pas... une bonne paella, mais... la bonne espagnole est absente.
On ne dit pas... mélodie en sous-sol, mais... gare notre voiture au parking.
On ne dit pas... je tripote, mais... j'ai trois amis.
On ne dit pas... le processus de paix est enclenché, mais... je vais lâcher une caisse.
On ne dit pas... étriqué, mais... j'ai bandé.
On ne dit pas... une dame pipi,... mais... un chef de cabinet.
On ne dit pas... je mastique,... mais... je m'en branle.
On ne dit pas... c'est alligator, mais... c'est Mouloud qui a raison.
On ne dit pas... allopathie, mais... vous êtes en communication avec un.
On ne dit pas... un pinailleur, mais... ... un mari infidèle.
On ne dit pas... Loto sportif, mais... une voiture GTI.
On ne dit pas... allégro, mais... vas y boudin.
On ne dit pas... j'alphabétise, mais... ... j'ai fait une connerie.
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
