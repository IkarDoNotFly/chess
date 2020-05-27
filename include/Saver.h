#pragma once

#include "Chessboard.h"
#include "Figure.h"

#include <memory>
#include <string>

class Saver {
    std::string fileName;
    std::string dumpFigure(const PFigure& fig) const;
    PFigure restoreFigure(const std::string& data) const;

public:
    explicit Saver(std::string filename = "./defailtSavefile.txt");
    void saveCheckboard(const PChessboard& checkboard) const;
    PChessboard loadCheckboard() const;
};

typedef std::shared_ptr<Saver> PSaver;