
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
        if (field.name_string().compare("Authorization") == 0) {
          for (auto it: ctrl->getToken()) {
            if (it.second->getToken().compare(List::split(field.value(), " ")[1]) == 0) return true;
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
    ctrl->init();
    ctrl->getRouter()->setPrefix("/v1");

    ctrl->getRouter()->addRoute(POST, "getToken", [ctrl](Context &ctx) {
      if (boost::json::parse(ctx.getRequest().body()).as_object().at("security").as_string().compare(MDP) == 0)  {
        fillResponse(ctx, ctrl->j_getToken(ctx));
        return;
      }
      ctx.getResponse().result(http::status::unauthorized);
      ctx.getResponse().body() = "{'statut':'Error','code':'" + to_string(UNAUTHORIZED) + "','description':'" + List::codeError(UNAUTHORIZED) + "'}";
      ctx.getResponse().set(http::field::content_type, "application/json");
    });

    ctrl->getRouter()->addRoute(POST, "/getInfos", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_getInfos(ctx));
    });

    ctrl->getRouter()->addRoute(GET, "/getHabitants", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_getHabitants(ctx));
    });

    ctrl->getRouter()->addRoute(GET, "/getEquipage", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_getEquipage(ctx));
    });

    ctrl->getRouter()->addRoute(GET, "/getInventory", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_getInventory(ctx));
    });

    ctrl->getRouter()->addRoute(GET, "/getHierarchy", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_getHierarchy(ctx));
    });

    ctrl->getRouter()->addRoute(POST, "/promote", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_promote(ctx));
    });

    ctrl->getRouter()->addRoute(DELETE, "/kill", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_kill(ctx));
    });

    ctrl->getRouter()->addRoute(POST, "/exchangeItem", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_exchangeItem(ctx));
    });

    ctrl->getRouter()->addRoute(POST, "/attack", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_attack(ctx));
    });

    ctrl->getRouter()->addRoute(PUT, "/addEntities", [ctrl](Context &ctx) {
      if (checkAuthorizedRequest(ctrl, ctx)) fillResponse(ctx,  ctrl->j_add_entities(ctx));
     });

    std::cout << "Server starting on port " << ctrl->getServeur()->getPort() << std::endl;
    ctrl->getServeur()->run();
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
