#pragma once
#include <matplot/matplot.h>
#include <vector>
#include "GRID.h"



class CellChangeTracker {
private:
    std::vector<int> births;
    std::vector<int> deaths;

public:
    void TrackChanges(const Grid& grid, const Grid& previousGrid) {
        int birthCount = 0;
        int deathCount = 0;

        for (const auto& cell : grid.GetAliveCells()) {
            if (!previousGrid.GetCell(cell.row, cell.column)) {
                birthCount++;
            }
        }

        for (const auto& cell : previousGrid.GetAliveCells()) {
            if (!grid.GetCell(cell.row, cell.column)) {
                deathCount++;
            }
        }

        births.push_back(birthCount);
        deaths.push_back(deathCount);
    }

    const std::vector<int>& GetBirths() const { return births; }
    const std::vector<int>& GetDeaths() const { return deaths; }



    void plot() { // plt isn't working properly, can't use classic update way
        using namespace matplot;
        static auto fig = figure(true);
        static double total_births = 0.0;
        static double total_deaths = 0.0;
        static bool initialized = false;

        if (!initialized) {
            fig->size(800, 600);
            title("Cumulative Births and Deaths Comparison");
            initialized = true;
        }
        total_births += births.back();
        total_deaths += deaths.back(); 
        std::vector<double> data = { total_births, total_deaths };
        fig->current_axes()->clear();
        bar(data); 
        fig->current_axes()->x_axis().ticklabels({ "Total Births", "Total Deaths" });
        fig->draw();
    }













};
