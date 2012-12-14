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
function experian_civil_form($nodeID, $ssn, $mode) {
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
function experian_address_form($nodeID, $ssn, $mode) {
  $form = array();
  
  $json = getAddressHistory($ssn, $mode);
  
  /*
  _saveNode($nodeID, $json, DATATYPE_ADDRESS);
  
  $history = json_decode($json, true);
  
  if(!empty($history)) {  
    $historyJSON = json_encode($history["xmlgw"]["search_response"]["response_data"]);
  }
  
  $form['jsonView'] = array(
		'#markup' => _getMarkup($historyJSON)
	);
	*/
	
	$form['jsonView'] = array(
		'#markup' => json_pretty($json, array("format"=>"html"))
	);
		
  return $form;
}


function getCriminalHistory($firstName, $lastName, $dateOfBirth, $ssn, $mode = "TESTING") {
  
  if($mode == "TESTING") {
  
    $xml = file_get_contents(dirname(__FILE__)."/example_criminal.xml");
    
  } else {
  
    /* PRODUCTION */
    $url = "https://www.appcheckdata.com/ws_criminal3/criminal.svc/xml?".
    "account=".urlencode(EXPERIAN_USERNAME).
    "&key=".urlencode(EXPERIAN_PASSWORD).
    "&ssn=".urlencode($ssn).
    "&lastname=".urlencode($lastName).
    "&firstname=".urlencode($firstName).
    "&DOB_yyyymmdd=".urlencode($dateOfBirth).
    "&disclaimers_agree=true".
    "&search_type=0".
    "&source_layout=5".
    "&ref=CS";
    $xml = file_get_contents($url);
  }
  
  return _xmlToJSON($xml);
}

function getCivilHistory($ssn, $mode = "TESTING") {


  if($mode == "TESTING") {
    $xml = file_get_contents(dirname(__FILE__)."/example_civil.xml");  
  } else {
  
    /* PRODUCTION */
    $url = "https://www.appcheckdata.com/xmlcivil/index.php?".
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
    $xmlPostData = '<?xml version="1.0"?>'.
      '<xmlgw>'.
       '<session>'.
            '<user_id>'.EXPERIAN_USERNAME.'</user_id>'.
            '<password>'.EXPERIAN_PASSWORD.'</password>'.
            '<customer_reference>Emerging Firms</customer_reference>'.
       '</session>'.
       '<search_request>'.
            '<search>stpeople</search>'.
            '<search_identifier>search-id</search_identifier>'.
            '<search_criteria>'.
            '<ssn>'.$ssn.'</ssn>'.
            '</search_criteria>'.
       '</search_request>'.
      '</xmlgw>';
        
    $postdata = http_build_query(array("request"=> urlencode($xmlPostData)));
    
    $opts = array('http' =>
        array(
            'method'  => 'POST',
            'header'  => 'Content-type: application/x-www-form-urlencoded',
            'content' => $postdata
        )
    );
    
    //echo '<pre>' . xmlpp($xmlPostData, true) . '</pre><br/>';  
    
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































/**
 * Pretty-print JSON string
 *
 * Use 'format' option to select output format - currently html and txt supported, txt is default
 * Use 'indent' option to override the indentation string set in the format - by default for the 'txt' format it's a tab
 *
 * @param string $json Original JSON string
 * @param array $options Encoding options
 * @return string
 */
function json_pretty($json, $options = array())
{
    $tokens = preg_split('|([\{\}\]\[,])|', $json, -1, PREG_SPLIT_DELIM_CAPTURE);
    $result = '';
    $indent = 0;

    $format = 'txt';

    //$ind = "\t";
    $ind = "    ";

    if (isset($options['format'])) {
        $format = $options['format'];
    }

    switch ($format) {
        case 'html':
            $lineBreak = '<br />';
            $ind = '&nbsp;&nbsp;&nbsp;&nbsp;';
            break;
        default:
        case 'txt':
            $lineBreak = "\n";
            //$ind = "\t";
            $ind = "    ";
            break;
    }

    // override the defined indent setting with the supplied option
    if (isset($options['indent'])) {
        $ind = $options['indent'];
    }

    $inLiteral = false;
    foreach ($tokens as $token) {
        if ($token == '') {
            continue;
        }

        $prefix = str_repeat($ind, $indent);
        if (!$inLiteral && ($token == '{' || $token == '[')) {
            $indent++;
            if (($result != '') && ($result[(strlen($result) - 1)] == $lineBreak)) {
                $result .= $prefix;
            }
            $result .= $token . $lineBreak;
        } elseif (!$inLiteral && ($token == '}' || $token == ']')) {
            $indent--;
            $prefix = str_repeat($ind, $indent);
            $result .= $lineBreak . $prefix . $token;
        } elseif (!$inLiteral && $token == ',') {
            $result .= $token . $lineBreak;
        } else {
            $result .= ( $inLiteral ? '' : $prefix ) . $token;

            // Count # of unescaped double-quotes in token, subtract # of
            // escaped double-quotes and if the result is odd then we are 
            // inside a string literal
            if ((substr_count($token, "\"") - substr_count($token, "\\\"")) % 2 != 0) {
                $inLiteral = !$inLiteral;
            }
        }
    }
    return $result;
}

/** Prettifies an XML string into a human-readable and indented work of art 
 *  @param string $xml The XML as a string 
 *  @param boolean $html_output True if the output should be escaped (for use in HTML) 
 */  
function xmlpp($xml, $html_output=false) {  
    $xml_obj = new SimpleXMLElement($xml);  
    $level = 4;  
    $indent = 0; // current indentation level  
    $pretty = array();  
      
    // get an array containing each XML element  
    $xml = explode("\n", preg_replace('/>\s*</', ">\n<", $xml_obj->asXML()));  
  
    // shift off opening XML tag if present  
    if (count($xml) && preg_match('/^<\?\s*xml/', $xml[0])) {  
      $pretty[] = array_shift($xml);  
    }  
  
    foreach ($xml as $el) {  
      if (preg_match('/^<([\w])+[^>\/]*>$/U', $el)) {  
          // opening tag, increase indent  
          $pretty[] = str_repeat(' ', $indent) . $el;  
          $indent += $level;  
      } else {  
        if (preg_match('/^<\/.+>$/', $el)) {              
          $indent -= $level;  // closing tag, decrease indent  
        }  
        if ($indent < 0) {  
          $indent += $level;  
        }  
        $pretty[] = str_repeat(' ', $indent) . $el;  
      }  
    }     
    $xml = implode("\n", $pretty);     
    return ($html_output) ? htmlentities($xml) : $xml;  
} 
