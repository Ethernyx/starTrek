
#include "include/Controller.hh"
#include <iostream>
#include  "lib_func/List.hh"

bool checkAuthorizedRequest(Controller *ctrl, Context &ctx) {
  /*if (ctx.getParam()..has_header("Authorization")) {
        std::string auth_header = req["Authorization"].to_string();
        if (auth_header.rfind("Bearer ", 0) == 0) {
            token = auth_header.substr(7); // Supprimer "Bearer "
        }
    }*/
   //for (auto it = ctx.getRequest().begin(); it != ctx.getRequest().end(); it++) cout << it->value() <<endl;
   for (const auto& field : ctx.getRequest()) {
        if (strcmp((char *)field.name(), "Authorization") == 0) {
          for (auto it: ctrl->getToken()) {
            if (it->getToken().compare(List::split(field.value(), " ")[1]) == 0) return true;
          }
        }
    }
    return false;
}

void  fillResponse(Context &ctx, string response) {
      cout << response << endl;
      if (boost::json::parse(response).as_object().at("statut").as_string().compare("Success") == 0) ctx.getResponse().result(http::status::ok);
      else  ctx.getResponse().result(http::status::bad_request);
      ctx.getResponse().body() = response;
      ctx.getResponse().set(http::field::content_type, "application/json");
}

int main(void) {
  try {

    Controller *ctrl = new Controller();
    ctrl->init(NULL);
    ctrl->getRouter()->setPrefix("/v1");

    ctrl->getRouter()->addRoute(POST, "get_token", [ctrl](Context &ctx) {
      if (boost::json::parse(ctx.getRequest().body()).as_object().at("security").as_string().compare(MDP) == 0)  {
        fillResponse(ctx, ctrl->j_getToken(ctx));
        return;
      }
      ctx.getResponse().result(http::status::unauthorized);
      ctx.getResponse().body() = "{'statut':'Error','code':'" + to_string(UNAUTHORIZED) + "','description':'" + List::codeError(UNAUTHORIZED) + "'}";
      ctx.getResponse().set(http::field::content_type, "application/json");
    });

    ctrl->getRouter()->addRoute(POST, "/get_infos", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_getInfos(ctx));
      
    });
/*
    ctrl->getRouter()->addRoute(POST, "/person", [ctrl](auto &ctx) {
      ctrl->createPerson(ctx);
    });

    ctrl->getRouter()->addRoute(GET, "/person/{id}", [ctrl](auto &ctx) {
      ctrl->getPersonById(ctx);
    });

    ctrl->getRouter()->addRoute(DELETE, "/person/{id}", [ctrl](auto &ctx) {
      ctrl->deletePersonById(ctx);
    });*/


    std::cout << "Server starting on port " << ctrl->getServeur()->getPort() << std::endl;
    ctrl->getServeur()->run();
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
