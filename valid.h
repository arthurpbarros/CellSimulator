#ifndef VALID
#define VALID
#include <cstring> // memset, memcpy
#include <iostream>
#include <iostream>
#include <string.h> //strlen
#include <string> //std::string,compare
#include <sstream> //std::stringstream
#include <fstream> //ifstream
#include <dirent.h> //opendir
#include <vector> //std::vector

   /// Represents a Color as a RGB entity.
   struct Color
   {
       //=== Alias
       typedef unsigned char color_t; //!< Type of a color channel.
       /// Identifies each color channel.
       enum channel_e : color_t { R=0, //!< Red channel.
                                  G=1, //!< Green channel.
                                  B=2 //!< Blue channel
       };

       //=== Members
       color_t channels[3]; //!< Stores each of the color channels, R, G, and B.
       //=== Methods
       /// Creates a color.
       Color( color_t r=0, color_t g=0, color_t b=0 ) : channels{r,g,b} {/*empty*/}
       /// Copy constructor.
       Color( const Color& clone )
       {
           std::memcpy( channels, clone.channels, sizeof(color_t)*3 );
       }
       /// Assignment operator.
       Color& operator=( const Color& rhs )
       {
           if ( &rhs != this )
               std::memcpy( channels, rhs.channels, sizeof(color_t)*3 );
           return *this;
       }
       /// Comparison operator.
       bool operator==( const Color& rhs )
       {
           return not std::memcmp( channels, rhs.channels, sizeof(color_t)*3 );
       }
   };

   /*
   std::map< std::string, Color > color_pallet;
   color_pallet.insert( std::make_pair( "BLACK", Color{0,0,0} ) );
   */

   // A basic color pallete.
   static const Color BLACK         = Color{0,0,0}      ; //!< Black.
   static const Color BLUE          = Color{0,0,255}    ; //!< Blue.
   static const Color WHITE         = Color{255,255,255}; //!< White.
   static const Color DARK_GREEN    = Color{0,100,0}    ; //!< Dark green.
   static const Color GREEN         = Color{0,250,0}    ; //!< Green.
   static const Color RED           = Color{255,0,0}    ; //!< Red.
   static const Color CRIMSON       = Color{220,20,60}  ; //!< Crimson (kind of red).
   static const Color LIGHT_BLUE    = Color{135,206,250}; //!< Light blue.
   static const Color LIGHT_GREY    = Color{210,210,210}; //!< Light blue.
   static const Color DEEP_SKY_BLUE = Color{0,191,255}  ; //!< Deep blue.
   static const Color DODGER_BLUE   = Color{30,144,255} ; //!< Another bluish color.
   static const Color STEEL_BLUE    = Color{70,130,180} ; //!< Yet another bluish color.
   static const Color YELLOW        = Color{255,255,0}  ; //!< Yellow.
   static const Color LIGHT_YELLOW  = Color{255,255,153}; //!< Light yellow.

  Color get_Color(std::string color){
      if(color.compare("BLACK") == 0){
        return BLACK;
      }else if(color.compare("BLUE") == 0){
        return BLUE;
      }else if(color.compare("WHITE") == 0){
        return WHITE;
      }else if(color.compare("DARK_GREEN") == 0){
        return DARK_GREEN;
      }else if(color.compare("DEEP_SKY_BLUE") == 0){
        return DEEP_SKY_BLUE;
      }else if(color.compare("DODGER_BLUE") == 0){
        return DODGER_BLUE;
      }else if(color.compare("GREEN") == 0){
        return GREEN;
      }else if(color.compare("LIGHT_BLUE") == 0){
        return LIGHT_BLUE;
      }else if(color.compare("LIGHT_GREY") == 0){
        return LIGHT_GREY;
      }else if(color.compare("LIGHT_YELLOW") == 0){
        return LIGHT_YELLOW;
      }else if(color.compare("RED") == 0){
        return RED;
      }else if(color.compare("STEEL_BLUE") == 0){
        return STEEL_BLUE;
      }else if(color.compare("WHITE") == 0){
        return WHITE;
      }else{
        return YELLOW;
      }

  }
  //Represent a list of parametres
  struct Params{
    bool help = false;
    std::string imgdir = "img";
    size_t maxgen = 0;
    size_t fps = 0;
    size_t blocksize = 5;
    std::string input_dir;
    Color bkgcolor{GREEN};
    Color alivecolor{RED};
    std::string outfile;
    bool valid = false;
  };
  Params p;
//Converte elemento do argv, de tamanho t para String.
std::string convert (char * str, size_t t){
	std::stringstream s;
	size_t i;
	for (i = 0; i < t; i++){
		s << str[i];
	}
	return s.str();
}

void valid_arguments(size_t argc, char ** argv){
	std::string aux;
	std::string flags[] = {"--h","--help","--fps","--imgdir","--maxgen","--outfile","--alivecolor","--bkgcolor","--blocksize"};
	std::string colors[] = {"BLACK", "BLUE", "CRIMSON", "DARK_GREEN", "DEEP_SKY_BLUE", "DODGER_BLUE","GREEN",
	 "LIGHT_BLUE", "LIGHT_GREY", "LIGHT_YELLOW", "RED", "STEEL_BLUE","WHITE","YELLOW"};
	std::vector<size_t> atr_valids; //Conta quantas flags e argumentos validos foram verificados
	//Params p;	
	if(argc >= 2){
		size_t args;
		for(args = 1; args < argc;args++){
			aux = convert(argv[args],strlen(*(argv+args))/sizeof(char));
			for(std::string flag : flags){
				if(aux.compare(flag) == 0){
					//Se a flag de ajuda foi solicitava, for a única flag e a primeira
					if((flag.compare("--h") == 0 || flag.compare("--help") == 0) && args == 1 && argc == 2){ 
						p.help = true;
						std::cout << "--help ativa\n"; 
					//Verifica se existe um argumento depois
					}else if(flag.compare("--fps") == 0 && args+1 < argc){
						//Capta o próximo argumento e verifica se é numero 
						aux = convert(argv[args+1],strlen(*(argv+args+1))/sizeof(char)); //Evita falha de Segmentação 
						try{
							int a = std::stoi(aux);
							if(a > 0){
								p.fps = a;
								std::cout << "--fps ativa\n";
								atr_valids.push_back(args); atr_valids.push_back(args+1);
							}
						}catch(std::exception const & e){}
						//Read in https://stackoverflow.com/questions/13470822/c-error-while-using-atoi
					//Verifica se existe um argumento depois
					}else if(flag.compare("--imgdir") == 0 && args+1 < argc){
						aux = convert(argv[args+1],strlen(*(argv+args+1))/sizeof(char));
						DIR * dir;
						dir = opendir(aux.c_str());
						if(dir){
							p.imgdir = aux;
							std::cout << "--imgdir ativa\n";
							atr_valids.push_back(args); atr_valids.push_back(args+1); 
						}
						//Read of https://www.techiedelight.com/convert-char-to-string-cpp/
					}else if(flag.compare("--maxgen") == 0 && args+1 < argc){
						aux = convert(argv[args+1],strlen(*(argv+args+1))/sizeof(char)); 
						try{
							int a = std::stoi(aux);
							if(a > 0) {
								p.maxgen = a;
								std::cout << "--maxgen ativa\n";
								atr_valids.push_back(args); atr_valids.push_back(args+1);
							} 
						}catch(std::exception const & e){}
					}else if(flag.compare("--outfile") == 0 && args+1 < argc){
						aux = convert(argv[args+1],strlen(*(argv+args+1))/sizeof(char));
						std::ifstream ifs;
						ifs.open(aux);
						if(ifs.is_open()){
							std::cout << aux << " outfile\n";
							atr_valids.push_back(args); atr_valids.push_back(args+1); 
						}else{
							std::ofstream ofs;
							ofs.open(aux,std::ofstream::out);
							ofs.close();
						}
						p.outfile = aux;
						std::cout << "--outfile ativa\n";
						ifs.close();
					}else if(flag.compare("--blocksize") == 0 && args+1 < argc){
						aux = convert(argv[args+1],strlen(*(argv+args+1))/sizeof(char));
						try{
							int a = std::stoi(aux);
							if(a > 0){
								p.blocksize = a;
								std::cout << "--blocksize ativa\n";
								atr_valids.push_back(args); atr_valids.push_back(args+1);
							} 
						}catch(std::exception const & e){}
					}else if(flag.compare("--alivecolor") == 0 && args+1 < argc){
						aux = convert(argv[args+1],strlen(*(argv+args+1))/sizeof(char));
						for(std::string color: colors){
							if(aux.compare(color) == 0){
								p.alivecolor = get_Color(color);
								std::cout << "--alivecolor ativa\n" << color << "\n";
								atr_valids.push_back(args); atr_valids.push_back(args+1); 
							}
						}
					}else if(flag.compare("--bkgcolor") == 0 && args+1 < argc){
						aux = convert(argv[args+1],strlen(*(argv+args+1))/sizeof(char));
						for(std::string color: colors){
							if(aux.compare(color) == 0){
								p.bkgcolor = get_Color(color);
								std::cout << "--bkgcolor ativa\n" << color << "\n";
								atr_valids.push_back(args); atr_valids.push_back(args+1); 
							}
						}
					}
				}
			}
		}


		size_t i,j;
		bool existe;
		for(i = 1; i < argc; i++){
			existe = false;
			for(j = 0; j < atr_valids.size() && existe == false;j++){
				existe = atr_valids.at(j) == i? true:false;
			}
			if(existe == false){
				aux = convert(argv[i],strlen(*(argv+i))/sizeof(char));
				if((aux.substr(0,2)).compare("--") != 0){
					std::ifstream ifs;
					ifs.open(aux);
					if(ifs.is_open()){
						p.input_dir = aux;
						std::cout << "--arquivo de entrada ativo\n";
						p.valid = true;
					}
					ifs.close();
					i = argc; //End Loops
				}
			}
		}
	}
}

bool get_help(void){ return p.help;}

size_t get_maxgen(void){ return p.maxgen;}

size_t get_fps(void){ return p.fps;}

size_t get_blocksize(void){ return p.blocksize;}

std::string get_input_dir(void){ return p.input_dir;}

Color get_bkgColor(void){return p.bkgcolor; }

Color get_aliveColor(void){return p.alivecolor;}

std::string get_outfile(void){return p.outfile;}

bool is_valid(void){return p.valid;}

std::string get_imgdir(void){ return p.imgdir; }
#endif