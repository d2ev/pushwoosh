# pushwoosh
It required different setup for both https and http protocol.

### https 
It will not work with self-signed certificates (https/ssl). You should get SSL certificate signed by trusted Authority.
Push notifications don't work in "Incognito" mode
For pushwoosh account settings for https follow the below instructions here - 
http://docs.pushwoosh.com/docs/chrome-web-push
http://docs.pushwoosh.com/docs/firefox-web-push

Website settings:
1. Download Pushwoosh Web Push SDK https://cdn.pushwoosh
.com/webpush/PushwooshWebSDKFiles.zip or follow documentation - 
http://docs.pushwoosh.com/docs/web-sdk-20

2. Get Pushwoosh Web Push SDK and unzip it. You should have the following files:
    * manifest.json
    * pushwoosh-service-worker-light.js
    * pushwoosh-service-worker-dark.js
 
3. Open manifest.json and make the following changes:
    *  Change name and short_name to the name of your website.
    * Change gcm_sender_id to your Google Project Number. Please keep in mind
     that Google Project Number is usually a 12-digit number, and it can't contain any letters. 
     
4. Place all these files to top-level root of your website directory. Make 
sure the following URLs are publicly accessible: 
    * https://yoursite.com/manifest.json
    * https://yoursite.com/pushwoosh-service-worker-light.js
    * https://yoursite.com/pushwoosh-service-worker-dark.js
     
### http
Enable settings push notifications for Chrome and Firefox http websites.
For pushwoosh account settings for http follow the instruction here - 
http://docs.pushwoosh.com/docs/chrome-web-push-for-http-websites
