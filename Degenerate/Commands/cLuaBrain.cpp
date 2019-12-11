#include "cLuaBrain.h"

#include "Commands.h"

#include <iostream>

//int KillAllHumans(lua_State *L)
//{
//	// There are 3 things on the stack: "Justin", 47, 3.14159 
//	const char* name = lua_tostring(L, 1);	// get "Justin"		
//	int age = lua_tonumber(L, 2);			// "Cat"
//	float pi = lua_tonumber(L, 3);			// 3.14159
//
//	std::cout << "KillAllHumans(): "
//		<< name << ", " << age << ", " << pi << std::endl;
//	return 0;
//}

cLuaBrain::cLuaBrain()
{
	//this->m_p_vecGOs = nullptr;

	// Create new Lua state.
	// NOTE: this is common to ALL script in this case
	this->m_pLuaState = luaL_newstate();

	luaL_openlibs(this->m_pLuaState);					/* Lua 5.3.3 */

//	lua_pushcfunction( this->m_pLuaState, l_KillAllHumans );
//	lua_setglobal( this->m_pLuaState, "WhatBenderTheRobotSays" );

	//lua_pushcfunction( this->m_pLuaState, KillAllHumans);
	//lua_setglobal( this->m_pLuaState, "JustinTrudeauIsOurPM" );

	//// 	static int l_UpdateObject( lua_State *L );		// c function
	//lua_pushcfunction( this->m_pLuaState, cLuaBrain::l_UpdateObject );
	//lua_setglobal( this->m_pLuaState, "setObjectState" );

	//lua_pushcfunction( this->m_pLuaState, cLuaBrain::l_GetObjectState );
	//lua_setglobal( this->m_pLuaState, "getObjectState" );
	lua_pushcfunction(this->m_pLuaState, cLuaBrain::CreateCommand);
	lua_setglobal(this->m_pLuaState, "CreateCommand");
	lua_pushcfunction(this->m_pLuaState, cLuaBrain::AddCommandToGroup);
	lua_setglobal(this->m_pLuaState, "AddCommandToGroup");


	return;
}

cLuaBrain::~cLuaBrain()
{
	lua_close(this->m_pLuaState);
	return;
}


// Saves (and overwrites) any script
// scriptName is just so we can delete them later
void cLuaBrain::LoadScript( std::string scriptName, 
					        std::string scriptSource )
{
	this->m_mapScripts[scriptName] = scriptSource;
	return;
}


void cLuaBrain::DeleteScript( std::string scriptName )
{
	// TODO: delete this scritp
	return;
}

// Passes a pointer to the game object vector
//void cLuaBrain::SetObjectVector( std::vector< cGameObject* >* p_vecGOs )
//{
//	//this->m_p_vecGOs = p_vecGOs;
//	return;
//}

void cLuaBrain::RunThis(std::string theLuaScript)
{
	int error = luaL_loadstring( this->m_pLuaState,
								theLuaScript.c_str() );

	if (error != 0 /*no error*/)
	{
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "Error running Lua script: ";
		std::cout << this->m_decodeLuaErrorToString(error) << std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;
	}

	// execute funtion in "protected mode", where problems are 
	//  caught and placed on the stack for investigation
	error = lua_pcall(this->m_pLuaState,	/* lua state */
					  0,	/* nargs: number of arguments pushed onto the lua stack */
					  0,	/* nresults: number of results that should be on stack at end*/
					  0);	/* errfunc: location, in stack, of error function.
							if 0, results are on top of stack. */
	if (error != 0 /*no error*/)
	{
		std::cout << "Lua: There was an error..." << std::endl;
		std::cout << this->m_decodeLuaErrorToString(error) << std::endl;

		std::string luaError;
		// Get error information from top of stack (-1 is top)
		luaError.append(lua_tostring(this->m_pLuaState, -1));

		// Make error message a little more clear
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "Error running Lua script: ";
		std::cout << luaError << std::endl;
		std::cout << "-------------------------------------------------------" << std::endl;
		// We passed zero (0) as errfunc, so error is on stack)
		lua_pop(this->m_pLuaState, 1);  /* pop error message from the stack */

	}

	return;
}




// Call all the active scripts that are loaded
void cLuaBrain::Update(float deltaTime)
{
//	std::cout << "cLuaBrain::Update() called" << std::endl;
	for( std::map< std::string /*name*/, std::string /*source*/>::iterator itScript = 
		 this->m_mapScripts.begin(); itScript != this->m_mapScripts.end(); itScript++ )
	{

		// Pass the script into Lua and update
//		int error = luaL_loadbuffer(L, buffer, strlen(buffer), "line");

		std::string curLuaScript = itScript->second;

		int error = luaL_loadstring( this->m_pLuaState, 
									 curLuaScript.c_str() );

		if ( error != 0 /*no error*/)	
		{
			std::cout << "-------------------------------------------------------" << std::endl;
			std::cout << "Error running Lua script: ";
			std::cout << itScript->first << std::endl;
			std::cout << this->m_decodeLuaErrorToString(error) << std::endl;
			std::cout << "-------------------------------------------------------" << std::endl;
			continue;
		}

		// execute funtion in "protected mode", where problems are 
		//  caught and placed on the stack for investigation
		error = lua_pcall(this->m_pLuaState,	/* lua state */
						  0,	/* nargs: number of arguments pushed onto the lua stack */
						  0,	/* nresults: number of results that should be on stack at end*/
						  0);	/* errfunc: location, in stack, of error function. 
								   if 0, results are on top of stack. */
		if ( error != 0 /*no error*/)	
		{
			std::cout << "Lua: There was an error..." << std::endl;
			std::cout << this->m_decodeLuaErrorToString(error) << std::endl;

			std::string luaError;
			// Get error information from top of stack (-1 is top)
			luaError.append( lua_tostring(this->m_pLuaState, -1) );

			// Make error message a little more clear
			std::cout << "-------------------------------------------------------" << std::endl;
			std::cout << "Error running Lua script: ";
			std::cout << itScript->first << std::endl;
			std::cout << luaError << std::endl;
			std::cout << "-------------------------------------------------------" << std::endl;
			// We passed zero (0) as errfunc, so error is on stack)
			lua_pop(this->m_pLuaState, 1);  /* pop error message from the stack */

			continue;
		}

	}

	// TODO: Lots of Lua stuff here...
	return;
}

// Called by Lua
// Passes object ID, new velocity, etc.
// Returns valid (true or false)
// Passes: 
// - position (xyz)
// - velocity (xyz)
// called "setObjectState" in lua
///*static*/ int cLuaBrain::l_UpdateObject( lua_State *L )
//{
//	int objectID = lua_tonumber(L, 1);	/* get argument */
//	
//	// Exist? 
//	cGameObject* pGO = cLuaBrain::m_findObjectByID(objectID);
//
//	if ( pGO == nullptr )
//	{	// No, it's invalid
//		lua_pushboolean( L,  false );
//		// I pushed 1 thing on stack, so return 1;
//		return 1;	
//	}
//
//	// Object ID is valid
//	// Get the values that lua pushed and update object
//	pGO->x = lua_tonumber(L, 2);	/* get argument */
//	pGO->y = lua_tonumber(L, 3);	/* get argument */
//	pGO->z = lua_tonumber(L, 4);	/* get argument */
//	pGO->Vx = lua_tonumber(L, 5);	/* get argument */
//	pGO->Vy = lua_tonumber(L, 6);	/* get argument */
//	pGO->Vz = lua_tonumber(L, 7);	/* get argument */
//
//	lua_pushboolean( L, true );	// index is OK
//	
//	return 1;		// I'm returning ONE thing
//
//}

// Passes object ID
// Returns valid (true or false)
// - position (xyz)
// - velocity (xyz)
// called "getObjectState" in lua
///*static*/ int cLuaBrain::l_GetObjectState( lua_State *L )
//{
//	int objectID = lua_tonumber(L, 1);	/* get argument */
//	
//	// Exist? 
//	cGameObject* pGO = cLuaBrain::m_findObjectByID(objectID);
//
//	if ( pGO == nullptr )
//	{	// No, it's invalid
//		lua_pushboolean( L,  false );
//		// I pushed 1 thing on stack, so return 1;
//		return 1;	
//	}
//
//	// Object ID is valid
//	lua_pushboolean( L, true );	// index is OK
//	lua_pushnumber( L, pGO->x );		
//	lua_pushnumber( L, pGO->y );		
//	lua_pushnumber( L, pGO->z );		
//	lua_pushnumber( L, pGO->Vx );		
//	lua_pushnumber( L, pGO->Vy );		
//	lua_pushnumber( L, pGO->Vz );		
//	
//	return 7;		// There were 7 things on the stack
//}

/*static*/ 
//std::vector< cGameObject* >* cLuaBrain::m_p_vecGOs;


// returns nullptr if not found
///*static*/ cGameObject* cLuaBrain::m_findObjectByID( int ID )
//{
//	for ( std::vector<cGameObject*>::iterator itGO = cLuaBrain::m_p_vecGOs->begin(); 
//		  itGO != cLuaBrain::m_p_vecGOs->end(); itGO++ )
//	{
//		if ( (*itGO)->getID() == ID )
//		{	// Found it!
//			return (*itGO);
//		}
//	}//for ( std::vector<cGameObject*>::iterator itGO...
//	// Didn't find it
//	return nullptr;
//}


int cLuaBrain::CreateCommand(lua_State* L)
{
	
	std::string type = lua_tostring(L, 1);
	std::string name = lua_tostring(L, 2);
	std::string params = lua_tostring(L, 3);


	int response = MakeCommand(type, name, params);

	lua_pushinteger(L, response);

	return 1;
}

int cLuaBrain::AddCommandToGroup(lua_State* L)
{
	int command = lua_tointeger(L, 1);
	int group = lua_tointeger(L, 2);

	int response = ::AddCommandToGroup(command, group);

	lua_pushinteger(L, response);
	return 1;
}

std::string cLuaBrain::m_decodeLuaErrorToString( int error )
{
	switch ( error )
	{
	case 0:
		return "Lua: no error";
		break;
	case LUA_ERRSYNTAX:
		return "Lua: syntax error"; 
		break;
	case LUA_ERRMEM:
		return "Lua: memory allocation error";
		break;
	case LUA_ERRRUN:
		return "Lua: Runtime error";
		break;
	case LUA_ERRERR:
		return "Lua: Error while running the error handler function";
		break;
	}//switch ( error )

	// Who knows what this error is?
	return "Lua: UNKNOWN error";
}
