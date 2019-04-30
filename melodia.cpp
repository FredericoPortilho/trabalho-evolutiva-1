
#include "melodia.h"
#include <cstdlib>

std::default_random_engine melodia::_generator = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());

melodia::melodia(affective &p):
     qtdNotasMelodia(p.size())
{
        //std::iota(_melodia.begin(), _affective.end(), 0);
        std::uniform_int_distribution<int> pitch(0, 15);
        std::uniform_int_distribution<int> duration(0,4);
        std::vector<int> _duracoes ={1,2,4,8,16};

        //int r = *select_randomly(foo.begin(), foo.end());
        /*
        duration
        Note Duration Integer Used
        whole note 0
        dotted half 1
        half 2
        dotted quarter 3
        quarter 4
        dotted eigth 5
        eigth 6
        sixteenth 7
        */
         int duracao = 16;

        //std::vector<int> _escala{1, 3, 5, 6, 8, 10, 12, 13};
        //std::cout<< "Tamanho" << p.size()<< "\n\n" ;

         _melodia.resize(p.size());
         for(int i=0; i < p.size(); ++i){
            //disp(p);
            //_melodia.push_back(std::vector<std::pair<int, int> >());
            divideNota(p.getArousal(), duracao, i, this->qtdNotasMelodia);
        }

/*
        for (int i = 0; i < p.size(); ++i) {
            std::cout << _melodia.size() << "\n";
            for (int j = 0; j < _melodia[i].size(); ++j) {
                std::cout << " " << _melodia[i].size();
            }
            std::cout << "\n" ;
        }
*/


        for (int i = 0; i < _melodia.size(); ++i) {
            for (int j = 0; j < _melodia[i].size(); ++j) {
                this->_melodia[i][j].first = pitch(this->_generator);
                //this->_melodia[i].second = _duracoes[duration(this->_generator)];
            }
        }

        //disp(p);

}
/*
melodia::melodia(affective &p,  std::vector<int> &tamanhoFilho)
{
    _melodia.resize(p.size());
    for(int i=0; i<p.size();++i){
        _melodia[i].resize(tamanhoFilho[i]);
    }

}*/
melodia::melodia(affective &p,  int filho)
{

}


void melodia::disp(affective &p) {
    std::cout << "----------------------Solution---------------------" << std::endl;
    std::cout << "Numero de Notas: "<< this->qtdNotasMelodia<< "\n" << std::endl;
     for(int i=0; i<_melodia.size(); ++i){
        for(int j=0; j<_melodia[i].size(); ++j){
            std::cout << "" << this->_melodia[i][j].first << "/";
            std::cout << "" << this->_melodia[i][j].second << "\t";
        }
        std::cout << "\n";

    }
    std::cout << "----------------------------------------------------\n";

}


void melodia::divideNota(double arousal, int duracao, int i, int qtdNotasMelodia){
    std::uniform_real_distribution<double> d(0, 20);
    chanceDividir = d(this->_generator);
    //std::cout <<"T3: " << this->qtdNotasMelodia<<" ";
    if(chanceDividir > duracao || duracao == 1){
        //std::cout<< ">>>> IF- - " <<i <<"   " << duracao << "\n";
        //
        //std::vector<std::pair<int, int> > nota(0, duracao);
        _melodia[i].push_back(std::make_pair(0, duracao));
        //std::cout << " " << _melodia[i].size()<< "\n ";
        //std::cout << nota.first << " /t" << nota.second;
        //_melodia[i].push_back(nota);
    }
    else{
         //std::cout<< ">>>>--ELSE --";
         this->qtdNotasMelodia++;
         divideNota(arousal, duracao/2,  i, this->qtdNotasMelodia);
         divideNota(arousal, duracao/2,  i, this->qtdNotasMelodia);
    }
}


//----------------------------------------------------------------------
//                          AVALIA A MELODIA
//----------------------------------------------------------------------

int melodia::evaluate(affective &p) {
    //std::vector<int> _escala{1, 3, 5, 6, 8, 10, 12, 13};//escala maior
    std::vector<int>::iterator it;

    //Metricas Avaliação Melodia Comum
    /*
    1. SAME NOTE: Fitness Points: 17. The scale degree of the next note has not
    changed.
    2. ONE STEP: Fitness Points: 17. The scale degree of the next note has gone up
    or down one step.
    3. ONE THIRD: Fitness Points: 15. The scale degree of the next note has gone up
    or down two steps.
    4. ONE FOURTH: Fitness Points: 12. The scale degree of the next note has gone
    up or down three steps.
    5. ONE FIFTH: Fitness Points: 10. The scale degree of the next note has gone up
    or down four steps.
    6. OVER FIFTH: Fitness Points: -25. The scale degree of the next note is greater
    than four steps away.
    7. FOUR SEVEN: Fitness Points: -25. The current note is scale degree four and
    the next note is scale degree seven.
    8. SIXTEENTH NOTE: Fitness Points: -10. The current note is a sixteenth note.
    9. DRASTIC DURATION CHANGE: Fitness Points: -20. The duration change
    between the current note and the next note is more than four steps in table 1.
    10. BEGIN TONIC: Fitness Points: 50. The melody begins with the tonic note
    (scale degree 1).
    11. END TONIC: Fitness Points: 50. The melody ends in the tonic note (scale
    degree 1).
    */

    //Metricas relacionadas a arousal valencia
    /*

    */

    //disp(p);
    int total = 0;
    /*
    //Dentro da escala
    for (int i = 0; i < p.size() - 1; ++i) {
        it = find(_escala.begin(), _escala.end(), this->_melodia[i]);
        if ( it != _escala.end()){
            total++;
        }
    }
    */
    int numNotasCompassoAnterior = 0;
    int numNotasCompassoAtual = 0;
    int ultimo = 0;
    //disp(p);

    for(int i = 0; i < _melodia.size(); ++i) {
        for(int j =0; j<_melodia[i].size(); ++j){

            ultimo = j;

            // Avaliações comparam nota seguinte a anterior
            if(j != 0){
                int difPitch = std::abs(_melodia[i][j].first - _melodia[i][j-1].first); //diferenca entre notas
                int difDur = std::abs(_melodia[i][j].second - _melodia[i][j-1].second); //diferenca entre notas

                if (difPitch <= 4){
                    total += 10 + p.getArousal()*-5;
                    if (difPitch <= 3) total += 2 + p.getArousal()*-1;
                    if (difPitch <= 2) total += 3 + p.getArousal()*-1;
                    if (difPitch <= 1) total += 2 + p.getArousal()*-1;
                }
                else{
                    total -=25;
                    total += p.getArousal()*12.5;
                }


                //mudança drastica de duração
                if(difDur > 10){
                    total -= 20;
                    total -= p.getValencia()*10;
                }

                //pontua pausa
                if(_melodia[i][j].second == 0){
                    total += 10 + (p.getArousal())*_melodia[i][j].second*-1;
                }

                //tritono
                if(_melodia[i][j-1].first == 4 && _melodia[i][j].first == 7){
                    total -= 25;
                }
            }




            //nota muito curta ou longa
            if (_melodia[i][j].second == 1 || _melodia[i][j].second == 16){
                total -= 10;
            }


        }//fim for interno



        //comeca na tonica


        if(i != 0){
            int ant = _melodia[i-1].size();
            int atual =_melodia[i].size();
              //std::cout << _melodia[i].size() <<" " << _melodia[i-1].size() <<" " <<std::abs(atual - ant)<<"\n\n\n";
             total += std::abs(atual - ant)*p.getValencia()*-10;
        }
/**/


        //std::cout<< ultimo <<" ";
            //std::cout<< _melodia[i].size() <<" ";


        //Ultima nota maior que a primeira
        if ( _melodia[i][ultimo] > _melodia[i][0]){
            total = total + p.getArousal()*10;//premia arousal positivo, desconta arousal negativo
        }
        else {
            total = total + p.getArousal()*-10; //premia arousal negativo, desconta arousal positivo
        }

    }//fim for externo

    if(_melodia[0][0].first == 1 || _melodia[0][0].first == 8 || _melodia[0][0].first == 15){
            total += 10+5*p.getValencia()/_melodia.size();
    }

        //termina na tonica
    if(_melodia[p.size()-1][ultimo].first == 1 || _melodia[p.size()-1][ultimo].first == 8 || _melodia[p.size()-1][ultimo].first == 15){
        total += 10+5*p.getValencia()/_melodia.size();
    }
    //std::cout<< total/this->qtdNotasMelodia <<" ";
    total = total/this->qtdNotasMelodia;

    if (total < 0){
        // total = -100;
    }

    //total = total/_melodia.size();
    //std::cout << "AQUI 2";
    return total;
}



void melodia::mutation(affective &p, double mutation_strength) {
    std::uniform_int_distribution<int> pos(0.0,1.0);
    std::uniform_real_distribution<double> muta(0, 1);
    std::uniform_int_distribution<int> d(1,2);

    std::uniform_int_distribution<int> pitch(0,15);

    //creep Mutation

    for (int i = 0; i < _melodia.size(); ++i) {
        for(int j = 0; j < _melodia[i].size(); ++j){
            //altera uma das notas em +1 ou -1
            //size_t posPitchMuta = d(_generator);

            if(muta(_generator) < mutation_strength){
                if((d(_generator)%2 == 0 || _melodia[i][j].first == 0) && _melodia[i][j].first != 15)
                    this->_melodia[i][j].first += 1;
                else
                    this->_melodia[i][j].first -= 1;
            }
        }
    }

      /*
    //Random Setting
    for (int i = 0; i < _melodia.size(); ++i) {
        for(int j = 0; j < _melodia[i].size(); ++j){
            //altera uma das notas em +1 ou -1
            //size_t posPitchMuta = d(_generator);

            if(muta(_generator) > mutation_strength){
                this->_melodia[i][j].first = pitch(_generator);
            }
            //divideNota(p.getArousal(), _melodia[posDurMuta].second);

        }
    }*/



    // Smart approach:
    // std::binomial_distribution<double> d(p.size(), mutation_strength)
    // int n = d(_generator)
    // flip $n$ bits
}

melodia melodia::crossover(affective &p, melodia &rhs) {
    std::uniform_int_distribution<int> d(0,p.size()-1);
    //std::uniform_int_distribution<size_t> d(0,rhs._melodia.size()-1);
    int gerado = d(_generator);

    //child = rhs;
    //std::vector<std::pair <int, int> > melodiaChild;
    //int qtdNotas;


    //define tamanho melodia filho

    melodia child(p, 0);
    child._melodia.resize(p.size());
    child.qtdNotasMelodia=0;


    for (int i = 0; i < gerado; ++i) {
        child._melodia[i].resize(this->_melodia[i].size());
        for (int j = 0; j < child._melodia[i].size(); ++j){
            child._melodia[i][j] = this->_melodia[i][j];
            child.qtdNotasMelodia++;
        }
    }

    for (int i = gerado; i < p.size(); ++i) {
        child._melodia[i].resize(rhs._melodia[i].size());
        for (int j = 0; j < child._melodia[i].size(); ++j){
            child._melodia[i][j] = rhs._melodia[i][j];
            child.qtdNotasMelodia++;
        }
    }


    return child;
}

/*
int melodia::tamanho() {
    int numeroNotasMelodia=0;
    for(int i=0; i<_melodia.size();++i){
        for(int j=0; j<_melodia.size();++j){
            numeroNotasMelodia++;
        }
    }
    return numeroNotasMelodia;
}
*/


int melodia::tamanhoMelodia() {
        return this->qtdNotasMelodia;
}


double melodia::distance(affective &p, melodia &rhs, double max_dist) {
    double notas = (double)rhs.qtdNotasMelodia;

    return notas;
}




