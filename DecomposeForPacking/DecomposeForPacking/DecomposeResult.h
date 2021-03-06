#pragma once

#include <map>
#include <tuple>
#include "Part.h"
#include "DLXSolver.h"

using std::tuple;
using std::map;

// Map from part to its number of occurrences in a certain solution 
typedef map<PartPtr, int> PartsCount;
typedef std::shared_ptr<PartsCount> PartsCountPtr;
// Vector of tuples, of part orientation and its origin point, of a certain solution
typedef vector<tuple<PartOrientationPtr, Point>> PartLocationList; 
typedef std::shared_ptr<PartLocationList> PartLocationListPtr;

/** Represents the decomposition result. */
class DecomposeResult
{
public:
	/** Constructs a new decomposition result. It is composed of:
	 *  1) Parts count list of all solutions in the decomposition process
	 *  2) List of part location lists of all solutions in the decomposition process
	 */
	DecomposeResult(std::shared_ptr<vector<PartsCountPtr>> partsCountList, std::shared_ptr<vector<PartLocationListPtr>> listOfPartLocationLists);
	
	DecomposeResult();

	/** Dtor. */
	virtual ~DecomposeResult();

	void extend(PartsCountPtr partsCount, PartLocationListPtr partLocationList);

	void add(shared_ptr<DecomposeResult> decomposeResult);

	/** Returns the parts count list of all solutions. */
	std::shared_ptr<vector<PartsCountPtr>> getPartsCountList();
	
	/** Returns a vector of the number of parts in each solution. */
	std::shared_ptr<vector<int>> getSolutionsNumOfParts();

	/** Returns the list of part location lists of all solutions. */
	std::shared_ptr<vector<PartLocationListPtr>> getListOfPartLocationLists();

private:
	// Parts count list of all solutions in the decomposition process
	std::shared_ptr<vector<PartsCountPtr>> _partsCountList;
	// List of part location lists of all solutions in the decomposition process
	std::shared_ptr<vector<PartLocationListPtr>> _listOfPartLocationLists;
};

