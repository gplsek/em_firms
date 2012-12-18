<?php
//dpm($node);
?>
<div id="main-report-wrapper">
  <div id="main-report-inner">
    <div class="contain" id="report-header">
      <a href="/" id="logo" rel="home" title="Home"> <img alt="Home" src="/sites/all/themes/earlyiq/logo.png" /> </a>
      <h1>
        Enterprise Management Report</h1>
      <div id="reported-company">
        <div class="left">
          <h2><?php= $company_name ?></h2>
          <p><?php= $company_description ?></p>
          <p class="address"><?php= $company_address ?></p>
          <p class="phone">Phone: <?php= $company_phone ?> Fax: <?php= $company_fax ?></p>
          <p class="website"><a href="<?php= $company_url ?>" target="_blank"><?php= $company_url ?></a></p>
        </div>
        <div class="right">
          <label id="company-titles">Key Executives and Shareholders</label>
          <ul>
            <?php
            foreach ($officers as $officer) {
              echo '<li><span class="title">' . $officer['title'] . '</span> - ' . $officer['fullname'] . '</li>';
            }
            ?>
          </ul>
        </div>
      </div>
    </div>
    <div id="report-body">
      <div class="report-group toggle-group">
        <div class="group-header expand-group">
          <h3>
            Business Entity Check</h3>
          <div class="rating">
            <label>total</label>
            <div class="stars <?php= $report_bec['stars'] ?>">
              5</div>
          </div>
          <div class="toggle opened" rel="report-BEC">
            CLOSE</div>
          <div class="toggle closed" rel="report-BEC">
            MORE INFO</div>
        </div>
        <div class="group-body toggle-container active" id="report-BEC">
          <ul id="group-body-items">
            <?php show_listitems($report_bec); ?>
          </ul>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header no-details">
          <h3>
            TQ Score<sup>TM</sup></h3>
          <div class="rating">
            <label>total</label>
            <div class="stars <?php= $report_bec['stars'] ?>">
              5</div>
          </div>
          <div class="no-toggle">
            Highest available score - very low probability of scam</div>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header">
          <h3>
            Background Verification</h3>
          <div class="rating">
            <label>total</label>
            <div class="stars five">
              5</div>
          </div>
          <div class="toggle opened" rel="report-BV">
            CLOSE</div>
          <div class="toggle closed" rel="report-BV">
            MORE INFO</div>
        </div>
        <div class="group-body toggle-container" id="report-BV">
          <ul id="group-body-items">
            <?php show_listitems($report_bv); ?>
          </ul>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header">
          <h3>
            Criminal Records Check</h3>
          <div class="rating">
            <label>total</label>
            <div class="stars five">
              5</div>
          </div>
          <div class="toggle opened" rel="report-CRC">
            CLOSE</div>
          <div class="toggle closed" rel="report-CRC">
            MORE INFO</div>
        </div>
        <div class="group-body toggle-container" id="report-CRC">
          <ul id="group-body-items">
            <?php show_listitems($report_crc); ?>
          </ul>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header">
          <h3>
            Civil Records Check</h3>
          <div class="rating">
            <label>total</label>
            <div class="stars four-half">
              4.5</div>
          </div>
          <div class="toggle opened" rel="report-CivRC">
            CLOSE</div>
          <div class="toggle closed" rel="report-CivRC">
            MORE INFO</div>
        </div>
        <div class="group-body toggle-container" id="report-CivRC">
          <ul id="group-body-items">
            <?php show_listitems($report_civrc); ?>
          </ul>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header no-details">
          <h3>
            Patriot Act Check</h3>
          <div class="rating">
            <label>total</label>
            <div class="stars five">
              5</div>
          </div>
          <div class="no-toggle">
            No records indicate conflict with US Patriot Act compliance</div>
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
?>
