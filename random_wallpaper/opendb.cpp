
int opendb(char** dbpath)
{
	//sqlite3-zeiger
	sqlite3*	Database;
	//
	std::string path = dbpath

	if(sqlite3_open(Path.c_str(), &Database) != SQLITE_OK)
	{ cout << "Fehler beim Oeffnen: " << sqlite3_errmsg(Database) << endl;
	return 1;
	}	
	return Database;
}
