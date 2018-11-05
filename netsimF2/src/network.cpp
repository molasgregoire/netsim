#include "network.h"
#include "random.h"
#include <algorithm>

//constructeur (par defaut), pour le moment vide
	Network::Network() 
	{}

//redefinit la taille la liste values des noeud
//imcomplete ?
	void Network::resize(const size_t& taille)
	{
			values.resize( taille );
			//on attribue de nouvelle valeur aleatoires entre 0 et 1 aux neurones
			//il est possible que des valeurs identiques apparaissent
			//RNG.uniform_double(values);
			RNG.normal(values);
		
	}

//creer n liens entre les noeuds de position a et b dans le tableau de values
//verifier si cela est possible, et ou si ce lien n'existe pas déjà
	bool Network::add_link(const size_t& a , const size_t& b )
	{		
		//exeptions non acceptables
			if( a >= values.size() or b >= values.size() or a == b )
			{
					return false;
			}
			
			//verification que le lien n'existe pas déjà pour eviter de créer des doublons
			for( auto item : links )
			{
				//if( item == std::pair<size_t,size_t>(a,b) or item == std::pair<size_t,size_t>(b,a) )
				if( ( item.first == a && item.second == b ) or ( item.first == b && item.second == a ) )
				{
					return false;
					//return true;
				}
			}
			
			//toute les conditions vérifiées, on insert le nouveau lien dans la liste
			//	std::cout<< "add link " << a << " & " << b << std::endl;
			links.insert( std::pair<size_t,size_t>(a,b) );
				
			return true;
			
	}

//on redefinit le tableau values
	size_t Network::set_values(const std::vector<double>& tab )
	{
		//remise a zero
		values.clear();
		links.clear();
		
		values = tab;
		
		return values.size();
	}

///VOIR AVEC ASSISTANT
 //on va creer des liens entre les noeud existant en iterant sur le tableau de noeud values
 //mecanisme imparfait je pense
	size_t Network::random_connect(const double& mean_deg)
	{
		//valeur de retour >> total des connection creees
		size_t sigma(0);
		
		//remise à zero des liens
		links.clear();
		
		std::vector<int> connections;
		connections.resize( values.size() );
		
		RNG.poisson( connections , mean_deg );
		
		for( size_t i(0) ; i < values.size() ; i++ )
		{
			for( int j(0) ; j < connections[i] ; j++ )
			{
				while( !add_link( i , size_t(RNG.uniform_double( 0 , values.size() ) ))){};
				sigma++;
			}
		}
		
		

		return sigma;
	}
	
	//number of nodes = la taille de values
	size_t Network::size() const
	{
		return values.size();
	}
	
	//nombre de lien du noeud numero n
	//on admet que le reste du programme est correct, donc pas de doublon ou de lien sur soit meme
	size_t Network::degree(const size_t &_n) const
	{
		size_t sigma(0);
		
		for(auto item : links)
		{
				if( item.first == _n or item.second == _n )
				{
						sigma++;
				}
		}
		
		return sigma;
	}
	
	//donne la valeur du Neme noeud
	//si n depasse la taille du tableau on retournera la dernière valeur par defaut
	double Network::value(const size_t &_n) const
	{
		if( _n < values.size() )
		{
			return values[_n];
		}
		else{
			return values[values.size()];
		}		
	}
	

	std::vector<double> Network::sorted_values() const
	{
		std::vector<double> tab;

		tab = values;
		
		sort(tab.begin(), tab.end()); 
		 std::reverse(tab.begin(),tab.end());
		
		return tab;
	}
	
/*! All neighbors (linked) nodes of node no *n* */
//en plus il faut  trier les valuers pour correspondre aux tests
	std::vector<size_t> Network::neighbors(const size_t& pos) const
	{
		std::vector<size_t> tab;
		
		for( auto item : links )
		{
			if( item.first == pos )
			{
				tab.push_back( item.second );
			}
			
			if( item.second == pos )
			{
				tab.push_back( item.first );
			}
			
		}
		
		 sort(tab.begin(), tab.end()); 
		 std::reverse(tab.begin(),tab.end());
		
		
		return tab;
	}

