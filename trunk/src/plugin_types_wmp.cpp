/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "plugin_types.h"

gchar *GetMIMEDescription()
{
    gchar MimeTypes[4000];
    GConfClient *gconf;
    gboolean wmp_disabled;
    
    g_type_init();
    gconf = gconf_client_get_default();
    wmp_disabled = gconf_client_get_bool(gconf, DISABLE_WMP, NULL);
    g_object_unref(G_OBJECT(gconf));

    if (wmp_disabled) {
        return NULL;
    } else {

        g_strlcpy(MimeTypes,
                  "application/asx:*:Media Files;"
                  "video/x-ms-asf-plugin:*:Media Files;"
                  "video/x-msvideo:avi,*:AVI;"
                  "video/msvideo:avi,*:AVI;"
                  "application/x-mplayer2:*:Media Files;"
                  "application/x-ms-wmv:wmv,*:Microsoft WMV video;"
                  "video/x-ms-asf:asf,asx,*:Media Files;"
                  "video/x-ms-wm:wm,*:Media Files;"
                  "video/x-ms-wmv:wmv,*:Microsoft WMV video;"
                  "audio/x-ms-wmv:wmv,*:Windows Media;"
                  "video/x-ms-wmp:wmp,*:Windows Media;"
                  "application/x-ms-wmp:wmp,*:Windows Media;"
                  "video/x-ms-wvx:wvx,*:Windows Media;"
                  "audio/x-ms-wax:wax,*:Windows Media;"
                  "audio/x-ms-wma:wma,*:Windows Media;"
                  "application/x-drm-v2:asx,*:Windows Media;"
                  "audio/wav:wav,*:Microsoft wave file;"
                  "audio/x-wav:wav,*:Microsoft wave file;", sizeof(MimeTypes));

        return g_strdup(MimeTypes);

    }
}

NPError PluginGetValue(NPPVariable variable, void *value)
{
    NPError err = NPERR_NO_ERROR;

    // some sites use this description to figure out what formats can be played. So we have to make sure the 
    // description matches the features

    if (variable == NPPVpluginNameString) {
        *((const char **) value) = "Windows Media Player Plugin";
    }
    if (variable == NPPVpluginDescriptionString) {
        *((const char **) value) =
            "<a href=\"http://dekorte.homeip.net/download/gnome-mplayer/\">Gecko Media Player</a> "
            VERSION
            "<br><br>Video Player Plug-in for QuickTime, RealPlayer and Windows Media Player streams using <a href=\"http://mplayerhq.hu\">MPlayer</a>";

    }

    if (variable == NPPVpluginNeedsXEmbed) {
        *((PRBool *) value) = PR_TRUE;
    }

    if ((variable != NPPVpluginNameString)
        && (variable != NPPVpluginDescriptionString)
        && (variable != NPPVpluginNeedsXEmbed)) {
        err = NPERR_INVALID_PARAM;
    }

    return err;

}
