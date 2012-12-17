<?php
//dpm($node);

  $company_name = "[Company Name]";
  $company_description = "[Company Description]";
  $company_address = "[Company Address]";
  $company_phone = "[Company Phone]";
  $company_fax = "[Company Fax]";
  $company_url = "http://www.companyurl.com";
  $officers = array();
  
  $tqScore = $node->field_tq_score["und"][0]["value"]; // decimal
  $backgroundVerification = $node->field_background_verification["und"][0]["value"]; // bool
  $criminalRecordsCheck = $node->field_criminal_records_check["und"][0]["value"]; // decimal
  $civilRecordsCheck = $node->field_criminal_records_check["und"][0]["value"]; // decimal
  $patriotActCheck = $node->field_patriot_act_check["und"][0]["value"]; // decimal
  /*
  
  $ = $node->["und"][0]["value"];
  $ = $node->["und"][0]["value"];
  $ = $node->["und"][0]["value"];
  $ = $node->["und"][0]["value"];
  $ = $node->["und"][0]["value"];
  $ = $node->["und"][0]["value"];
  $ = $node->["und"][0]["value"];
  $ = $node->["und"][0]["value"];
  */
?>
<div id="main-report-wrapper">
  <div id="main-report-inner">
    <div class="contain" id="report-header">
      <a href="/" id="logo" rel="home" title="Home"> <img alt="Home" src="/sites/all/themes/seven_doublemthemes/logo.png" /> </a>
      <h1>
        Enterprise Management Report</h1>
      <div id="reported-company">
        <div class="left">
          <h2><?= $company_name ?></h2>
          <p><?= $company_description ?></p>
          <p class="address"><?= $company_address ?></p>
          <p class="phone">Phone: <?= $company_phone ?> Fax: <?= $company_fax ?></p>
          <p class="website"><a href="<?= $company_url ?>" target="_blank"><?= $company_url ?></a></p>
        </div>
        <div class="right">
          <label id="company-titles">Key Executives and Shareholders</label>
          <ul>
            <?php
            foreach ($officers as $officer) {
              echo '<li>'.
                      '<span class="title">' . $officer['title'] . 
                      '</span> - ' . $officer['fullname'] . 
                    '</li>';
            }
            
            ?>
          </ul>
        </div>
      </div>
    </div>
    <div id="report-body">
      
      <div class="report-group toggle-group">
        <div class="group-header no-details">
          <h3>TQ Score<sup>TM</sup></h3>
          <div class="rating">
            <label>total</label>
            <div class="stars <?= decimalToWord($tqScore) ?>">
              <?= $tqScore ?></div>
          </div>
          <div class="no-toggle"></div>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header">
          <h3>Background Verification</h3>
          <div class="rating"><label><?=$backgroundVerification?"PASSED":"FAILED"?></label></div>
          <div class="toggle opened" rel="report-BV">
            CLOSE</div>
          <div class="toggle closed" rel="report-BV">
            MORE INFO</div>
        </div>
        <div class="group-body toggle-container" id="report-BV">
          <ul id="group-body-items">
            <?=getList($node, "background_verification")?>
          </ul>
        </div>
      </div>
      
      <div class="report-group toggle-group">
        <div class="group-header">
          <h3>
            Criminal Records Check</h3>
          <div class="rating">
            <label>total</label>
            <div class="stars <?= decimalToWord($criminalRecordsCheck) ?>">
              <?= $criminalRecordsCheck ?></div>
          </div>
          <div class="toggle opened" rel="report-CRC">
            CLOSE</div>
          <div class="toggle closed" rel="report-CRC">
            MORE INFO</div>
        </div>
        <div class="group-body toggle-container" id="report-CRC">
          <ul id="group-body-items">
            <?=getList($node, "criminal_records")?>
          </ul>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header">
          <h3>
            Civil Records Check</h3>
          <div class="rating">
            <label>total</label>
            <div class="stars <?= decimalToWord($civilRecordsCheck) ?>">
              <?= $civilRecordsCheck ?></div>
          </div>
          <div class="toggle opened" rel="report-CivRC">
            CLOSE</div>
          <div class="toggle closed" rel="report-CivRC">
            MORE INFO</div>
        </div>
        <div class="group-body toggle-container" id="report-CivRC">
          <ul id="group-body-items">
            <?=getList($node, "civil_records")?>
          </ul>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header no-details">
          <h3>Patriot Act Check</h3>
          <div class="rating"><label><?=$patriotActCheck?"PASSED":"FAILED"?></label></div>
          <div class="no-toggle"></div>
        </div>
      </div>
    </div>
  </div>
</div>
<?php

function show_listitems($items) {
  foreach ($items as $item) {
    echo '<li>';
    echo '  <span class="left-col">' . $item['title'] . '</span> ';
    echo '  <span class="report-icon ' . $item['class'] . '" title="' . $item['icon-description'] . '">' . $item['rating'] . '</span>';
    echo '  <div class="right-col">';
    echo '    <p>' . $item['explanation'] . '</p>';
    echo '  </div>';
    echo '</li>';
  }
}

function getList($node, $listName) {
  $html = "";
  if($listName == "background_verification") {
    $html = getBackgroundVerificationList($node);
  } else if($listName == "criminal_records") {
    $html = getCriminalRecordsList($node);
  } else if($listName == "civil_records") {
    $html = getCivilRecordsList($node);
  }
  return $html;
}

function getBackgroundVerificationList($node) {
  $html = getItemHTML($node, "field_name_verification").
          getItemHTML($node, "field_positive_id_auth").
          getItemHTML($node, "field_alias_search");
  return $html;
}

function getCriminalRecordsList($node) {
  $html = getItemHTML($node, "field_nat_felony_search").
          getItemHTML($node, "field_nat_misdmnr_search");
  return $html;
}

function getCivilRecordsList($node) {
  $html = getItemHTML($node, "field_judgements").
          getItemHTML($node, "field_tax_liens").
          getItemHTML($node, "field_bankruptcies").
          getItemHTML($node, "field_pending_litigations");
  return $html;
}

function getItemHTML($node, $fieldName) {
  
  $icon = getItemIcon($node, $fieldName);
  
  return '<li>'.
          '<span class="left-col" 
                 title="'.getHelpText($fieldName).'">'.
              getFieldLabel($fieldName).
          '</span>'.
          '<span class="report-icon '.$icon.'" 
                 title="'.getIconHelpText($icon).'">'.
              $icon.
          '</span>'.
          '<div class="right-col">'.
            '<p>'.getDescriptionText($node, $fieldName).'</p>'.
          '</div>'.
        '</li>';
}


function decimalToWord($decimal) {
  $word = "zero";
  
  if($decimal > 0.00 && $decimal < 1.00) {
    $word = "half";
  } else if($decimal == 1.00) {
    $word = "one";
  } else if($decimal > 1.00 && $decimal < 2.00) {
    $word = "one-half";
  } else if($decimal == 2.00) {
    $word = "two";
  } else if($decimal > 2.00 && $decimal < 3.00) {
    $word = "two-half";
  } else if($decimal == 3.00) {
    $word = "three";
  } else if($decimal > 3.00 && $decimal < 4.00) {
    $word = "three-half";
  } else if($decimal == 4.00) {
    $word = "four";
  } else if($decimal > 4.00 && $decimal < 5.00) {
    $word = "four-half";
  } else if($decimal == 5.00) {
    $word = "five";
  }
  
  return $word;
}

function getItemIcon($node, $fieldName) {

  $fieldObject = $node->$fieldName;
  $value = $fieldObject["und"][0]["value"];
  
  $fieldInfoObject = field_info_field($fieldName);
  $values = $fieldInfoObject["settings"]["allowed_values"];
  
  return strtolower($values[$value]);

}

function getHelpText($fieldName) {
  $fieldInfo = field_info_instance('node', $fieldName, 'report_card');
  return $fieldInfo["description"];
}

function getFieldLabel($fieldName) {
  $fieldInfo = field_info_instance('node', $fieldName, 'report_card');
  return $fieldInfo["label"];
}

function getDescriptionText($node, $fieldName) {
  $fieldName .= "_desc";
  $fieldObject = $node->$fieldName;
  return $fieldObject["und"][0]["value"];
}

function getIconHelpText($icon) {
  $helpText = "";
  if($icon == "pass") {
    $helpText = "Green.  This means everything for this line item checked out OK.";
  } else if($icon == "fail") {
    $helpText = "Failure.";
  } else if($icon == "note") {
    $helpText = "Informational.  This means information about this specific line item was found but likely doesn't warrant further investigation.";
  } else if($icon == "warn") {
    $helpText = "Warning.";
  }
}

?>
