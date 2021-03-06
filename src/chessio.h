// Copyright 1996-2008, 2013 by Jon Dart. All Rights Reserved
#ifndef __CHESSIO_H__
#define __CHESSIO_H__

#include "types.h"
#include "epdrec.h"
#include "board.h"
#include "arasvec.h"
#include "movearr.h"
#include <fstream>
#include <string>
#include <utility>

using namespace std;

// This class handles I/O of PGN, FEN and EPD files.
// Note: some functions are only used in the GUI.
//
class ChessIO
{
public:
    class Header : public pair<string, string> {
    public:
        Header() : pair<string, string>() {
        }
        Header(const string &tag, const string &val) :
        pair<string, string>(tag,val) {
        }
        const string &tag() const {
            return first;
        }
        const string &value() const {
            return second;
        }
    };

    // scan a PGN file, fill "contents" with strings.  Each string contains
    // a descriptive 1-line header followed by a tab and the file offset
    // of the game in decimal digits. 
    static int scan_pgn(istream &ifs, ArasanVector<string> &contents);

    // Store a PGN file with the specified headers
    static int store_pgn(ostream &ofs, MoveArray &moves,
                         const ColorType computer_side,
                         const string &result,
	                 ArasanVector<Header> &headers);

    static int store_pgn(ostream &ofs, MoveArray &moves,
                         const string &result,
	                 ArasanVector<Header> &headers);

    static int load_fen(istream &ifs, Board &board);
    static int store_fen(ostream &ofs, const Board &board);

    // read a PGN game header from the file.
    static void collect_headers(istream &game_file, 
      ArasanVector<Header> &hdrs, long &first);

    // get a specific header out of a collection of headers (returned
    // from collect_headers)
    static int get_header(const ArasanVector<Header> &hdrs, 
	  const string &key, string &val);

    // read an EPD file, return 1 if ok, 0 if EOF
    static int readEPDRecord(istream &ifs, Board &board, EPDRecord &out);
    
    enum TokenType { Number, GameMove, Result, 
                     OpenVar,
                     CloseVar,
                     NAG,
                     BlackMove,
                     Comment, Unknown, Ignore, Eof };

    struct Token {
        TokenType type;
        string val;
        Token() :
        type(Unknown),val("") {
        }
        Token(TokenType t, string v) :
        type(t),val(v) {
        }
    };

    // read the next token from the "body" of a PGN game.
    static Token get_next_token(istream &game_file);

    // return (in descr) a single-line description of a game, based on
    // its PGN headers (for game list display).
    static void get_game_description(const ArasanVector<Header> &hdrs, string &descr, long id);
private:
    static void add_header(ArasanVector <Header> &hdrs,
                    const string &key, const string & val);


};

#endif
