<?php

require_once("xml2json/xml2json.php");

define("EXPERIAN_USERNAME", "emerging");
define("EXPERIAN_PASSWORD", "dfgr^e3r9s");

define("DATATYPE_CIVIL", "civil");
define("DATATYPE_CRIMINAL", "criminal");
define("DATATYPE_ADDRESS", "address");


/**
 * Experian Form
 *
 */
function experian_test($form, &$form_state) {
  $form = array();
  
  if(!empty($form_state["rebuild"]) && !empty($form_state["values"])) {
    $data = $form_state["values"];
    
    $nodeID = null;
    //$nodeID = $data["node_id"];
    
    $mode = $data["mode"] ? "PRODUCTION" : "TESTING";
            
    if($data["product"] == "criminal") {
      $dob = $data["birthdate"]["year"].$data["birthdate"]["month"].$data["birthdate"]["day"];
      $form = experian_criminal_form($nodeID, $data["first_name"], $data["last_name"], $dob, $data["ssn"], $mode);
    }
    
    if($data["product"] == "civil") {
      $form = experian_civil_form($nodeID, $data["ssn"], $mode);
    }
    
    if($data["product"] == "address") {
      $form = experian_address_form($nodeID, $data["ssn"], $mode);
    }
    
  } else {
  
    $form['first_name'] = array(
  		'#title' => t('First Name'),
  		'#type' => 'textfield'
  	);
  	
  	$form['last_name'] = array(
  		'#title' => t('Last Name'),
  		'#type' => 'textfield'
  	);
  	
  	$form['birthdate'] = array(
  	  '#title' => t('Birthdate'),
  	  '#type' => 'date',
  	  '#description' => t('Select your birthdate'),
  	  '#default_value' => array(
  	  	    'month' => format_date(time(), 'custom', 'n'),
  	  	    'day' => format_date(time(), 'custom', 'j'),
  	  	    'year' => format_date(time(), 'custom', 'Y'),
          )
  	);
  	
  	$form['ssn'] = array(
  		'#title' => t('Social Security Number'),
  		'#type' => 'textfield'
  	);
  	
  	$form['product'] = array(
      '#type'=>'radios',
      '#required' => TRUE,
      '#options'=>array(
        "criminal"=>"Criminal",
        "civil"=>"Civil",
        "address"=>"Address"
      ),
      '#default_value' => 'criminal',

    );
  	
  	$form['mode'] = array(
      '#type' => 'checkbox',
      '#title'=>t('Live (Will cost money)'),
      '#default_value' => 0
    );
  	
  	$form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit')
    );
  }
  
	return $form;
}

/**
 * 
 */
function experian_test_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Entry point to get Criminal History
 * 
 * @return array a form in the Drupal Form API format
 */
function experian_criminal_form($nodeID, $firstName, $lastName, $dob, $ssn, $mode) {
  $form = array();
  
  $json = getCriminalHistory($firstName, $lastName, $dob, $ssn, $mode);
  _saveNode($nodeID, $json, DATATYPE_CRIMINAL);
  
  $history = json_decode($json, true);
  
  if(!empty($history["Search_results"]["Record"])) {
    $historyJSON = json_encode($history["Search_results"]["Record"]);
  } else {
    $historyJSON = json_encode($history);
  }
  
  $form['jsonView'] = array(
		'#markup' => _getMarkup($historyJSON)
	);
		
  return $form;
}

/**
 * Entry point to get Civil History
 * 
 * @return array a form in the Drupal Form API format
 */
function experian_civil_form($ssn, $mode) {
  $form = array();
  
  $json = getCivilHistory($ssn, $mode);
  _saveNode($nodeID, $json, DATATYPE_CIVIL);
  
  $history = json_decode($json, true);
  
  if(!empty($history)) {
    $historyJSON = json_encode($history["xmlgw"]["search_response"]["response_data"]);
  }
  
  $form['jsonView'] = array(
		'#markup' => _getMarkup($historyJSON)
	);
		
  return $form;
}

/**
 * Entry point to get Address History
 * 
 * Retrieves the data and saves it, then returns a drupal form
 *
 * @return array a form in the Drupal Form API format
 */
function experian_address_form($ssn, $mode) {
  $form = array();
  
  $json = getAddressHistory($ssn, $mode);
  _saveNode($nodeID, $json, DATATYPE_ADDRESS);
  
  $history = json_decode($json, true);
  
  if(!empty($history)) {  
    $historyJSON = json_encode($history["xmlgw"]["search_response"]["response_data"]);
  }
  
  $form['jsonView'] = array(
		'#markup' => _getMarkup($historyJSON)
	);
		
  return $form;
}


function getCriminalHistory($firstName, $lastName, $dateOfBirth, $ssn, $mode = "TESTING") {
  
  if($mode == "TESTING") {
  
    $xml = file_get_contents(dirname(__FILE__)."/example_criminal.xml");
    
  } else {
  
    /* PRODUCTION */
    $url = "https://www.appcheckdata.com/ws_criminal3/criminal.svc/xml/ssn?".
    "account=".urlencode(EXPERIAN_USERNAME).
    "&key=".urlencode(EXPERIAN_PASSWORD).
    "&ssn_source=1".
    "&ssn=".urlencode($ssn).
    "&lastname=".urlencode($lastName).
    "&firstname=".urlencode($firstName).
    "&DOB_yyyymmdd=".urlencode($dateOfBirth).
    "&disclaimers_agree=y".
    "&search_type= 0".
    "&source_layout=5". 
    "&ref=CS";
    
    $xml = file_get_contents($url);
    
    echo "RESPONSE[".htmlentities($xml)."]";
  }
  
  return _xmlToJSON($xml);
}

function getCivilHistory($ssn, $mode = "TESTING") {


  if($mode == "TESTING") {
    $xml = file_get_contents(dirname(__FILE__)."/example_civil.xml");  
  } else {
  
    /* PRODUCTION */
    $url = "https://www.appcheckdata.com/xmlcivil/index.php".
    "account=".urlencode(EXPERIAN_USERNAME).
    "&key=".urlencode(EXPERIAN_PASSWORD).
    "&ssn=".urlencode($ssn);
    $xml = file_get_contents($url);
    
  }
  
  return _xmlToJSON($xml);
}


function getAddressHistory($ssn, $mode = "TESTING") {
  
  if($mode == "TESTING") {
  
    $xml = file_get_contents(dirname(__FILE__)."/example_address.xml");  
    
  } else {
  
    /* PRODUCTION */  
    $postdata = http_build_query(array("request"=> urlencode('<?xml version="1.0"?>
      <xmlgw>
       <session>
            <user_id>'.EXPERIAN_USERNAME.'</user_id>
            <password>'.EXPERIAN_PASSWORD.'</password>
            <customer_reference>Emerging Firms</customer_reference>
       </session>
       <search_request>
            <search>stpeople</search>
            <search_identifier>search-id</search_identifier>
            <search_criteria>
            <ssn>'.$ssn.'</ssn>
            </search_criteria>
       </search_request>
      </xmlgw>')));
  
    $opts = array('http' =>
        array(
            'method'  => 'POST',
            'header'  => 'Content-type: application/x-www-form-urlencoded',
            'content' => $postdata
        )
    );
    
    $context  = stream_context_create($opts);
    
    $xml = file_get_contents('https://appcheckdata.com/xmlssn/ssntracer_pr.php', false, $context);
  }
  
  return _xmlToJSON($xml);
}

/**
 * Saves Civil/Criminal/Address History JSON to the given node
 *
 * @param int The id of the node
 * @param string The JSON string of the data
 * @param string The type of JSON data included (criminal, civil, address)
 */
function _saveNode($nodeID, $json, $dataType) {
  
  if(!empty($nodeID)) {
    // Save the data
    $node = node_load($nodeID);
    
    if(!empty($node)) {    
    
      if($dataType == DATATYPE_CIVIL) {
      
        $node->field_results_address_civil['und'][0]['value'] = $json;
        
      } else if($dataType == DATATYPE_CRIMINAL) {
      
        $node->field_results_address_criminal['und'][0]['value'] = $json;
        
      } else if($dataType == DATATYPE_ADDRESS) {
      
        $node->field_results_address_history['und'][0]['value'] = $json;
        
      }
      
      node_save($node);
    }
    
  }
}

function _getMarkup($json = "{}") {
  $markup = "";
  
  if ($path = libraries_get_path("jsonFormat")) {
    // Do something with the library, knowing the path, for instance:
    drupal_add_js($path . '/JSONFormat.js');
    drupal_add_css($path . '/JSONFormat.css');
    
    drupal_add_js(
      "jQuery(document).ready(function () {".
        "window.ImgCollapsed = '".url($path."/images/Collapsed.png")."';".
        "window.ImgExpanded = '".url($path."/images/Expanded.png")."';".
        "Process('".$json."');".
      "});",
      array('type' => 'inline', 'scope' => 'footer')  
    );
    
    $markup = '<div id="jsonView"></div>';
  } else {
    $markup = "COULD NOT FIND jsonFormat Library";
  }
  return $markup;
}


/**
 * Converts XML to JSON
 *
 * @param string xml
 * @return string json string
 */
function _xmlToJSON($xml) {

  $json = xml2json::transformXmlStringToJson($xml);
  return $json;
}