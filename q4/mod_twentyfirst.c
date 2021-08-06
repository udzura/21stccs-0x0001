#define CORE_PRIVATE
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "http_log.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <json-c/json.h>

module AP_MODULE_DECLARE_DATA twentyfirst_module;

typedef struct dir_config {
  unsigned int enabled;
} dir_config_t;

static void *twentyfirst_create_dir_config(apr_pool_t *p, char *_dirname)
{
  dir_config_t *conf = (dir_config_t *)apr_pcalloc(p, sizeof(dir_config_t));
  conf->enabled = 0;
  return conf;
}

static const char *twentyfirst_enable_dir_config(cmd_parms *cmd, void *mconfig, int flag)
{
  dir_config_t *dir_conf = (dir_config_t *)mconfig;
  dir_conf->enabled = flag;
  return NULL;
}

static void *twentyfirst_create_config(apr_pool_t *p, server_rec *server)
{
  return NULL;
}

static int twentyfirst_handler(request_rec *r) {
  struct timespec buf;
  dir_config_t *dir_conf = ap_get_module_config(r->per_dir_config, &twentyfirst_module);
  if (!dir_conf->enabled)
    return DECLINED;

  int i, ok = 0;
  json_object *obj;
  for (i = 0; i < 10; i++) {
    int f = open("/etc/dummy-conf.json", O_RDONLY|O_CLOEXEC);
    char buf[327680];
    if (read(f, buf, 327680) != 0) {
      obj = json_tokener_parse(buf);
      ok = 1;
    }
  }

  ap_set_content_type(r, "text/plain");
  ap_rprintf(r, "Welcome to 21stccs!\n");
  if (ok == 1) {
    ap_rprintf(r, "# JSON Loaded! %d\n", json_object_object_length(obj));
    free(obj);
  }
    
  return OK;
}

static const command_rec module_cmds[] =
  {
   AP_INIT_FLAG("twentyfirstEnabled", twentyfirst_enable_dir_config,
                NULL, ACCESS_CONF, "Enable sample module."),
   { NULL },
  };

static void register_hooks(apr_pool_t *p)
{
  ap_hook_handler(twentyfirst_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA twentyfirst_module =
  {
    STANDARD20_MODULE_STUFF,
    twentyfirst_create_dir_config,
    NULL,
    twentyfirst_create_config,
    NULL,
    module_cmds,
    register_hooks
  };
